/* -------------------------------------------

  Some modifications are copyrighted under:
  Amlal El Mahrouss

  Original author:
  Apple Inc

------------------------------------------- */

#pragma once

#include <stdint.h>

/// @note Based of:
/// https://opensource.apple.com/source/cctools/cctools-750/as/ppc-opcode.h.auto.html

#define kOpcodePPCCount (1073U)

/*
 * These defines are use in the cpus field of the instructions.  If the field
 * is zero it can execute on all cpus.  The defines are or'ed together.  This
 * information is used to set the cpusubtype in the resulting object file.
 */
#define CPU601 0x1
#define IMPL64 0x2
#define OPTIONAL 0x4
#define VMX 0x8
#define CPU970 0x10      /* added to OPTIONAL insts that the 970 has */
#define CPUMAHROUSS 0x12 /* optional mahrouss insts. */

enum OpcodeType {
  NONE,    /* no operand */
  JBSR,    /* jbsr pseudo op */
  PCREL,   /* PC relative (branch offset) */
  BADDR,   /* Branch address (sign extended absolute address) */
  D,       /* 16 bit displacement */
  DS,      /* 14 bit displacement (double word) */
  SI,      /* signed 16 bit immediate */
  UI,      /* unsigned 16 bit immediate */
  HI,      /* high 16 bit immediate (with truncation) */
  GREG,    /* general register */
  G0REG,   /* general register r1-r31 or 0 */
  FREG,    /* float register */
  VREG,    /* vector register */
  SGREG,   /* segment register */
  SPREG,   /* special register (or 10 bit number, 5 bit halves reversed) */
  BCND,    /* branch condition opcode */
  CRF,     /* condition register field */
  CRFONLY, /* condition register field only no expression allowed */
  sh,      /* 6 bit number (0 - 63) (sh field, split and reversed) */
  mb,      /* 6 bit number (0 - 63) (mb field, mb5 || mb0:4 reversed) */
  NUM,     /* number */
  SNUM,    /* signed number */
  NUM0,    /* number (where 1<<width is the same as 0) */
  MBE,     /* mask defined by MB and ME fields */
  FXM,     /* 8-bit mask with only one bit set */
  ZERO     /* the number zero */
};

struct CpuOpcodePPC {
  struct OpcodeType final {
    uint32_t offset : 5;
    uint32_t width : 5;
    uint32_t type : 6;
  };

  uint32_t    opcode;
  const char* name;  // c++ wants the string to be const, it makes sense here.
  OpcodeType  ops[5];
  uint32_t    cpus;
};

inline CpuOpcodePPC kOpcodesPowerPC[] = {
    {0x38000000, "addi", {{21, 5, GREG}, {16, 5, G0REG}, {0, 16, SI}}},
    {0x38000000, "li", {{21, 5, GREG}, {0, 16, SI}}},
    {0x3c000000, "addis", {{21, 5, GREG}, {16, 5, G0REG}, {0, 16, HI}}},
    {0x3c000000, "lis", {{21, 5, GREG}, {0, 16, HI}}},
    {0x30000000, "addic", {{21, 5, GREG}, {16, 5, GREG}, {0, 16, SI}}},
    {0x34000000, "addic.", {{21, 5, GREG}, {16, 5, GREG}, {0, 16, SI}}},
    {0x7c000214, "add", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000215, "add.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000614, "addo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000615, "addo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000014, "addc", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000015, "addc.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000414, "addco", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000415, "addco.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000114, "adde", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000115, "adde.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000514, "addeo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000515, "addeo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c0001d4, "addme", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0001d5, "addme.", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0005d4, "addmeo", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0005d5, "addmeo.", {{21, 5, GREG}, {16, 5, GREG}}},

    {0x7c000194, "addze", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c000195, "addze.", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c000594, "addzeo", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c000595, "addzeo.", {{21, 5, GREG}, {16, 5, GREG}}},

    {0x70000000, "andi.", {{16, 5, GREG}, {21, 5, GREG}, {0, 16, UI}}},
    {0x74000000, "andis.", {{16, 5, GREG}, {21, 5, GREG}, {0, 16, UI}}},
    {0x7c000038, "and", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000039, "and.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    {0x7c000078, "andc", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000079, "andc.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    {0x48000000, "b", {{2, 24, PCREL}}},
    {0x48000002, "ba", {{2, 24, BADDR}}},
    {0x48000001, "bl", {{2, 24, PCREL}}},
    {0x48000003, "bla", {{2, 24, BADDR}}},

    {0x48000001, "jbsr", {{0, 0, JBSR}, {2, 24, PCREL}}},
    {0x48000000, "jmp", {{0, 0, JBSR}, {2, 24, PCREL}}},

    {0x40000000, "bc", {{21, 5, NUM}, {16, 5, NUM}, {2, 14, PCREL}}},
    {0x40000002, "bca", {{21, 5, NUM}, {16, 5, NUM}, {2, 14, BADDR}}},
    {0x40000001, "bcl", {{21, 5, NUM}, {16, 5, NUM}, {2, 14, PCREL}}},
    {0x40000003, "bcla", {{21, 5, NUM}, {16, 5, NUM}, {2, 14, BADDR}}},

    {0x4c000420, "bcctr", {{21, 5, NUM}, {16, 5, NUM}}},
    {0x4c000420, "bcctr", {{21, 5, NUM}, {16, 5, NUM}, {11, 2, NUM}}},
    {0x4c000421, "bcctrl", {{21, 5, NUM}, {16, 5, NUM}}},
    {0x4c000421, "bcctrl", {{21, 5, NUM}, {16, 5, NUM}, {11, 2, NUM}}},
    {0x4c000020, "bclr", {{21, 5, NUM}, {16, 5, NUM}}},
    {0x4c000020, "bclr", {{21, 5, NUM}, {16, 5, NUM}, {11, 2, NUM}}},
    {0x4c000021, "bclrl", {{21, 5, NUM}, {16, 5, NUM}}},
    {0x4c000021, "bclrl", {{21, 5, NUM}, {16, 5, NUM}, {11, 2, NUM}}},

    /* Basic branch mnemonics (assember extended mnemonics) */
    /* { 0x42800000, "b",       {{2,14,PCREL}} }, overlaps */
    /* { 0x42800001, "bl",      {{2,14,PCREL}} }, overlaps */
    {0x41800000, "bt", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x41800001, "btl", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x40800000, "bf", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x40800001, "bfl", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x42000000, "bdnz", {{2, 14, PCREL}}},
    {0x42000001, "bdnzl", {{2, 14, PCREL}}},
    {0x41000000, "bdnzt", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x41000001, "bdnztl", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x40000000, "bdnzf", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x40000001, "bdnzfl", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x42400000, "bdz", {{2, 14, PCREL}}},
    {0x42400001, "bdzl", {{2, 14, PCREL}}},
    {0x41400000, "bdzt", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x41400001, "bdztl", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x40400000, "bdzf", {{16, 5, BCND}, {2, 14, PCREL}}},
    {0x40400001, "bdzfl", {{16, 5, BCND}, {2, 14, PCREL}}},

    /* { 0x42800002, "ba",      {{2,14,BADDR}} }, overlaps */
    /* { 0x42800003, "bla",     {{2,14,BADDR}} }, overlaps */
    {0x41800002, "bta", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x41800003, "btla", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x40800002, "bfa", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x40800003, "bfla", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x42000002, "bdnza", {{2, 14, BADDR}}},
    {0x42000003, "bdnzla", {{2, 14, BADDR}}},
    {0x41000002, "bdnzta", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x41000003, "bdnztla", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x40000002, "bdnzfa", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x40000003, "bdnzfla", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x42400002, "bdza", {{2, 14, BADDR}}},
    {0x42400003, "bdzla", {{2, 14, BADDR}}},
    {0x41400002, "bdzta", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x41400003, "bdztla", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x40400002, "bdzfa", {{16, 5, BCND}, {2, 14, BADDR}}},
    {0x40400003, "bdzfla", {{16, 5, BCND}, {2, 14, BADDR}}},

    {
        0x4e800020,
        "blr",
    },
    {0x4e800020, "blr", {{11, 2, NUM}}},
    {
        0x4e800021,
        "blrl",
    },
    {0x4e800021, "blrl", {{11, 2, NUM}}},
    {0x4d800020, "btlr", {{16, 5, BCND}}},
    {0x4d800020, "btlr", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4d800021, "btlrl", {{16, 5, BCND}}},
    {0x4d800021, "btlrl", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4c800020, "bflr", {{16, 5, BCND}}},
    {0x4c800020, "bflr", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4c800021, "bflrl", {{16, 5, BCND}}},
    {0x4c800021, "bflrl", {{16, 5, BCND}, {11, 2, NUM}}},
    {
        0x4e000020,
        "bdnzlr",
    },
    {0x4e000020, "bdnzlr", {{11, 2, NUM}}},
    {
        0x4e000021,
        "bdnzlrl",
    },
    {0x4e000021, "bdnzlrl", {{11, 2, NUM}}},
    {0x4d000020, "bdnztlr", {{16, 5, BCND}}},
    {0x4d000020, "bdnztlr", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4d000021, "bdnztlrl", {{16, 5, BCND}}},
    {0x4d000021, "bdnztlrl", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4c000020, "bdnzflr", {{16, 5, BCND}}},
    {0x4c000020, "bdnzflr", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4c000021, "bdnzflrl", {{16, 5, BCND}}},
    {0x4c000021, "bdnzflrl", {{16, 5, BCND}, {11, 2, NUM}}},
    {
        0x4e400020,
        "bdzlr",
    },
    {0x4e400020, "bdzlr", {{11, 2, NUM}}},
    {
        0x4e400021,
        "bdzlrl",
    },
    {0x4e400021, "bdzlrl", {{11, 2, NUM}}},
    {0x4d400020, "bdztlr", {{16, 5, BCND}}},
    {0x4d400020, "bdztlr", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4d400021, "bdztlrl", {{16, 5, BCND}}},
    {0x4d400021, "bdztlrl", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4c400020, "bdzflr", {{16, 5, BCND}}},
    {0x4c400020, "bdzflr", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4c400021, "bdzflrl", {{16, 5, BCND}}},
    {0x4c400021, "bdzflrl", {{16, 5, BCND}, {11, 2, NUM}}},

    {0x4c000420, "bctr", {{21, 5, NUM}, {16, 5, NUM}}},
    {
        0x4e800420,
        "bctr",
    },
    {0x4e800420, "bctr", {{11, 2, NUM}}},
    {0x4c000421, "bctrl", {{21, 5, NUM}, {16, 5, NUM}}},
    {
        0x4e800421,
        "bctrl",
    },
    {0x4e800421, "bctrl", {{11, 2, NUM}}},
    {0x4d800420, "btctr", {{16, 5, BCND}}},
    {0x4d800420, "btctr", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4d800421, "btctrl", {{16, 5, BCND}}},
    {0x4d800421, "btctrl", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4c800420, "bfctr", {{16, 5, BCND}}},
    {0x4c800420, "bfctr", {{16, 5, BCND}, {11, 2, NUM}}},
    {0x4c800421, "bfctrl", {{16, 5, BCND}}},
    {0x4c800421, "bfctrl", {{16, 5, BCND}, {11, 2, NUM}}},

    /* branch mnemonics incorporating conditions (assember extended mnemonics)
     */
    {0x41800000, "blt", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41800000, "blt", {{2, 14, PCREL}}},
    {0x41800001, "bltl", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41800001, "bltl", {{2, 14, PCREL}}},
    {0x40810000, "ble", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40810000, "ble", {{2, 14, PCREL}}},
    {0x40810001, "blel", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40810001, "blel", {{2, 14, PCREL}}},
    {0x41820000, "beq", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41820000, "beq", {{2, 14, PCREL}}},
    {0x41820001, "beql", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41820001, "beql", {{2, 14, PCREL}}},
    {0x40800000, "bge", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40800000, "bge", {{2, 14, PCREL}}},
    {0x40800001, "bgel", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40800001, "bgel", {{2, 14, PCREL}}},
    {0x41810000, "bgt", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41810000, "bgt", {{2, 14, PCREL}}},
    {0x41810001, "bgtl", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41810001, "bgtl", {{2, 14, PCREL}}},
    {0x40800000, "bnl", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40800000, "bnl", {{2, 14, PCREL}}},
    {0x40800001, "bnll", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40800001, "bnll", {{2, 14, PCREL}}},
    {0x40820000, "bne", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40820000, "bne", {{2, 14, PCREL}}},
    {0x40820001, "bnel", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40820001, "bnel", {{2, 14, PCREL}}},
    {0x40810000, "bng", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40810000, "bng", {{2, 14, PCREL}}},
    {0x40810001, "bngl", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40810001, "bngl", {{2, 14, PCREL}}},
    {0x41830000, "bso", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41830000, "bso", {{2, 14, PCREL}}},
    {0x41830001, "bsol", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41830001, "bsol", {{2, 14, PCREL}}},
    {0x40830000, "bns", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40830000, "bns", {{2, 14, PCREL}}},
    {0x40830001, "bnsl", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40830001, "bnsl", {{2, 14, PCREL}}},
    {0x41830000, "bun", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41830000, "bun", {{2, 14, PCREL}}},
    {0x41830001, "bunl", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x41830001, "bunl", {{2, 14, PCREL}}},
    {0x40830000, "bnu", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40830000, "bnu", {{2, 14, PCREL}}},
    {0x40830001, "bnul", {{16, 5, CRF}, {2, 14, PCREL}}},
    {0x40830001, "bnul", {{2, 14, PCREL}}},

    {0x41800002, "blta", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41800002, "blta", {{2, 14, BADDR}}},
    {0x41800003, "bltla", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41800003, "bltla", {{2, 14, BADDR}}},
    {0x40810002, "blea", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40810002, "blea", {{2, 14, BADDR}}},
    {0x40810003, "blela", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40810003, "blela", {{2, 14, BADDR}}},
    {0x41820002, "beqa", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41820002, "beqa", {{2, 14, BADDR}}},
    {0x41820003, "beqla", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41820003, "beqla", {{2, 14, BADDR}}},
    {0x40800002, "bgea", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40800002, "bgea", {{2, 14, BADDR}}},
    {0x40800003, "bgela", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40800003, "bgela", {{2, 14, BADDR}}},
    {0x41810002, "bgta", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41810002, "bgta", {{2, 14, BADDR}}},
    {0x41810003, "bgtla", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41810003, "bgtla", {{2, 14, BADDR}}},
    {0x40800002, "bnla", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40800002, "bnla", {{2, 14, BADDR}}},
    {0x40800003, "bnlla", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40800003, "bnlla", {{2, 14, BADDR}}},
    {0x40820002, "bnea", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40820002, "bnea", {{2, 14, BADDR}}},
    {0x40820003, "bnela", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40820003, "bnela", {{2, 14, BADDR}}},
    {0x40810002, "bnga", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40810002, "bnga", {{2, 14, BADDR}}},
    {0x40810003, "bngla", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40810003, "bngla", {{2, 14, BADDR}}},
    {0x41830002, "bsoa", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41830002, "bsoa", {{2, 14, BADDR}}},
    {0x41830003, "bsola", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41830003, "bsola", {{2, 14, BADDR}}},
    {0x40830002, "bnsa", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40830002, "bnsa", {{2, 14, BADDR}}},
    {0x40830003, "bnsla", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40830003, "bnsla", {{2, 14, BADDR}}},
    {0x41830002, "buna", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41830002, "buna", {{2, 14, BADDR}}},
    {0x41830003, "bunla", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x41830003, "bunla", {{2, 14, BADDR}}},
    {0x40830002, "bnua", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40830002, "bnua", {{2, 14, BADDR}}},
    {0x40830003, "bnula", {{16, 5, CRF}, {2, 14, BADDR}}},
    {0x40830003, "bnula", {{2, 14, BADDR}}},

    {0x4d800020, "bltlr", {{16, 5, CRF}}},
    {0x4d800020, "bltlr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d800020,
        "bltlr",
    },
    {0x4d800021, "bltlrl", {{16, 5, CRF}}},
    {0x4d800021, "bltlrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d800021,
        "bltlrl",
    },
    {0x4c810020, "blelr", {{16, 5, CRF}}},
    {0x4c810020, "blelr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c810020,
        "blelr",
    },
    {0x4c810021, "blelrl", {{16, 5, CRF}}},
    {0x4c810021, "blelrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c810021,
        "blelrl",
    },
    {0x4d820020, "beqlr", {{16, 5, CRF}}},
    {0x4d820020, "beqlr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d820020,
        "beqlr",
    },
    {0x4d820021, "beqlrl", {{16, 5, CRF}}},
    {0x4d820021, "beqlrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d820021,
        "beqlrl",
    },
    {0x4c800020, "bgelr", {{16, 5, CRF}}},
    {0x4c800020, "bgelr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c800020,
        "bgelr",
    },
    {0x4c800021, "bgelrl", {{16, 5, CRF}}},
    {0x4c800021, "bgelrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c800021,
        "bgelrl",
    },
    {0x4d810020, "bgtlr", {{16, 5, CRF}}},
    {0x4d810020, "bgtlr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d810020,
        "bgtlr",
    },
    {0x4d810021, "bgtlrl", {{16, 5, CRF}}},
    {0x4d810021, "bgtlrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d810021,
        "bgtlrl",
    },
    {0x4c800020, "bnllr", {{16, 5, CRF}}},
    {0x4c800020, "bnllr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c800020,
        "bnllr",
    },
    {0x4c800021, "bnllrl", {{16, 5, CRF}}},
    {0x4c800021, "bnllrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c800021,
        "bnllrl",
    },
    {0x4c820020, "bnelr", {{16, 5, CRF}}},
    {0x4c820020, "bnelr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c820020,
        "bnelr",
    },
    {0x4c820021, "bnelrl", {{16, 5, CRF}}},
    {0x4c820021, "bnelrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c820021,
        "bnelrl",
    },
    {0x4c810020, "bnglr", {{16, 5, CRF}}},
    {0x4c810020, "bnglr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c810020,
        "bnglr",
    },
    {0x4c810021, "bnglrl", {{16, 5, CRF}}},
    {0x4c810021, "bnglrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c810021,
        "bnglrl",
    },
    {0x4d830020, "bsolr", {{16, 5, CRF}}},
    {0x4d830020, "bsolr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d830020,
        "bsolr",
    },
    {0x4d830021, "bsolrl", {{16, 5, CRF}}},
    {0x4d830021, "bsolrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d830021,
        "bsolrl",
    },
    {0x4c830020, "bnslr", {{16, 5, CRF}}},
    {0x4c830020, "bnslr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c830020,
        "bnslr",
    },
    {0x4c830021, "bnslrl", {{16, 5, CRF}}},
    {0x4c830021, "bnslrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c830021,
        "bnslrl",
    },
    {0x4d830020, "bunlr", {{16, 5, CRF}}},
    {0x4d830020, "bunlr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d830020,
        "bunlr",
    },
    {0x4d830021, "bunlrl", {{16, 5, CRF}}},
    {0x4d830021, "bunlrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d830021,
        "bunlrl",
    },
    {0x4c830020, "bnulr", {{16, 5, CRF}}},
    {0x4c830020, "bnulr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c830020,
        "bnulr",
    },
    {0x4c830021, "bnulrl", {{16, 5, CRF}}},
    {0x4c830021, "bnulrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c830021,
        "bnulrl",
    },

    {0x4d800420, "bltctr", {{16, 5, CRF}}},
    {0x4d800420, "bltctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d800420,
        "bltctr",
    },
    {0x4d800421, "bltctrl", {{16, 5, CRF}}},
    {0x4d800421, "bltctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d800421,
        "bltctrl",
    },
    {0x4c810420, "blectr", {{16, 5, CRF}}},
    {0x4c810420, "blectr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c810420,
        "blectr",
    },
    {0x4c810421, "blectrl", {{16, 5, CRF}}},
    {0x4c810421, "blectrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c810421,
        "blectrl",
    },
    {0x4d820420, "beqctr", {{16, 5, CRF}}},
    {0x4d820420, "beqctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d820420,
        "beqctr",
    },
    {0x4d820421, "beqctrl", {{16, 5, CRF}}},
    {0x4d820421, "beqctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d820421,
        "beqctrl",
    },
    {0x4c800420, "bgectr", {{16, 5, CRF}}},
    {0x4c800420, "bgectr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c800420,
        "bgectr",
    },
    {0x4c800421, "bgectrl", {{16, 5, CRF}}},
    {0x4c800421, "bgectrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c800421,
        "bgectrl",
    },
    {0x4d810420, "bgtctr", {{16, 5, CRF}}},
    {0x4d810420, "bgtctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d810420,
        "bgtctr",
    },
    {0x4d810421, "bgtctrl", {{16, 5, CRF}}},
    {0x4d810421, "bgtctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d810421,
        "bgtctrl",
    },
    {0x4c800420, "bnlctr", {{16, 5, CRF}}},
    {0x4c800420, "bnlctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c800420,
        "bnlctr",
    },
    {0x4c800421, "bnlctrl", {{16, 5, CRF}}},
    {0x4c800421, "bnlctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c800421,
        "bnlctrl",
    },
    {0x4c820420, "bnectr", {{16, 5, CRF}}},
    {0x4c820420, "bnectr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c820420,
        "bnectr",
    },
    {0x4c820421, "bnectrl", {{16, 5, CRF}}},
    {0x4c820421, "bnectrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c820421,
        "bnectrl",
    },
    {0x4c810420, "bngctr", {{16, 5, CRF}}},
    {0x4c810420, "bngctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c810420,
        "bngctr",
    },
    {0x4c810421, "bngctrl", {{16, 5, CRF}}},
    {0x4c810421, "bngctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c810421,
        "bngctrl",
    },
    {0x4d830420, "bsoctr", {{16, 5, CRF}}},
    {0x4d830420, "bsoctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d830420,
        "bsoctr",
    },
    {0x4d830421, "bsoctrl", {{16, 5, CRF}}},
    {0x4d830421, "bsoctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d830421,
        "bsoctrl",
    },
    {0x4c830420, "bnsctr", {{16, 5, CRF}}},
    {0x4c830420, "bnsctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c830420,
        "bnsctr",
    },
    {0x4c830421, "bnsctrl", {{16, 5, CRF}}},
    {0x4c830421, "bnsctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c830421,
        "bnsctrl",
    },
    {0x4d830420, "bunctr", {{16, 5, CRF}}},
    {0x4d830420, "bunctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d830420,
        "bunctr",
    },
    {0x4d830421, "bunctrl", {{16, 5, CRF}}},
    {0x4d830421, "bunctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4d830421,
        "bunctrl",
    },
    {0x4c830420, "bnuctr", {{16, 5, CRF}}},
    {0x4c830420, "bnuctr", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c830420,
        "bnuctr",
    },
    {0x4c830421, "bnuctrl", {{16, 5, CRF}}},
    {0x4c830421, "bnuctrl", {{16, 5, CRF}, {11, 2, NUM}}},
    {
        0x4c830421,
        "bnuctrl",
    },

    {0x2c000000, "cmpi", {{21, 5, CRFONLY}, {16, 5, GREG}, {0, 16, SI}}},
    {0x2c000000, "cmpi", {{21, 5, CRFONLY}, {21, 1, NUM}, {16, 5, GREG}, {0, 16, SI}}},
    {0x2c000000, "cmpi", {{23, 3, NUM}, {16, 5, GREG}, {0, 16, SI}}},
    {0x2c000000, "cmpi", {{23, 3, NUM}, {21, 1, NUM}, {16, 5, GREG}, {0, 16, SI}}},
    {0x2c000000, "cmpwi", {{16, 5, GREG}, {0, 16, SI}}},
    {0x2c000000, "cmpwi", {{21, 5, CRFONLY}, {16, 5, GREG}, {0, 16, SI}}},
    {0x2c000000, "cmpwi", {{23, 3, NUM}, {16, 5, GREG}, {0, 16, SI}}},
    {0x2c200000, "cmpdi", {{16, 5, GREG}, {0, 16, SI}}},
    {0x2c200000, "cmpdi", {{21, 5, CRFONLY}, {16, 5, GREG}, {0, 16, SI}}},
    {0x2c200000, "cmpdi", {{23, 3, NUM}, {16, 5, GREG}, {0, 16, SI}}},

    {0x7c000000, "cmp", {{21, 5, CRFONLY}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000000, "cmp", {{21, 5, CRFONLY}, {21, 1, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000000, "cmp", {{23, 3, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000000, "cmp", {{23, 3, NUM}, {21, 1, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000000, "cmpw", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000000, "cmpw", {{21, 5, CRFONLY}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000000, "cmpw", {{23, 3, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c200000, "cmpd", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7c200000, "cmpd", {{21, 5, CRFONLY}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c200000, "cmpd", {{23, 3, NUM}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x28000000, "cmpli", {{21, 5, CRFONLY}, {16, 5, GREG}, {0, 16, UI}}},
    {0x28000000, "cmpli", {{21, 5, CRFONLY}, {21, 1, NUM}, {16, 5, GREG}, {0, 16, UI}}},
    {0x28000000, "cmpli", {{23, 3, NUM}, {16, 5, GREG}, {0, 16, UI}}},
    {0x28000000, "cmpli", {{23, 3, NUM}, {21, 1, NUM}, {16, 5, GREG}, {0, 16, UI}}},
    {0x28000000, "cmplwi", {{16, 5, GREG}, {0, 16, UI}}},
    {0x28000000, "cmplwi", {{21, 5, CRFONLY}, {16, 5, GREG}, {0, 16, UI}}},
    {0x28000000, "cmplwi", {{23, 3, NUM}, {16, 5, GREG}, {0, 16, UI}}},
    {0x28200000, "cmpldi", {{16, 5, GREG}, {0, 16, UI}}},
    {0x28200000, "cmpldi", {{21, 5, CRFONLY}, {16, 5, GREG}, {0, 16, UI}}},
    {0x28200000, "cmpldi", {{23, 3, NUM}, {16, 5, GREG}, {0, 16, UI}}},

    {0x7c000040, "cmpl", {{21, 5, CRFONLY}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000040, "cmpl", {{21, 5, CRFONLY}, {21, 1, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000040, "cmpl", {{23, 3, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000040, "cmpl", {{23, 3, NUM}, {21, 1, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000040, "cmplw", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000040, "cmplw", {{21, 5, CRFONLY}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000040, "cmplw", {{23, 3, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c200040, "cmpld", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7c200040, "cmpld", {{21, 5, CRFONLY}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c200040, "cmpld", {{23, 3, NUM}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000034, "cntlzw", {{16, 5, GREG}, {21, 5, GREG}}},
    {0x7c000035, "cntlzw.", {{16, 5, GREG}, {21, 5, GREG}}},
    {0x7c000074, "cntlzd", {{16, 5, GREG}, {21, 5, GREG}}, IMPL64},
    {0x7c000075, "cntlzd.", {{16, 5, GREG}, {21, 5, GREG}}, IMPL64},

    {0x4c000202, "crand", {{21, 5, NUM}, {16, 5, NUM}, {11, 5, NUM}}},
    {0x4c000102, "crandc", {{21, 5, NUM}, {16, 5, NUM}, {11, 5, NUM}}},
    {0x4c000242, "creqv", {{21, 5, NUM}, {16, 5, NUM}, {11, 5, NUM}}},
    {0x4c0001c2, "crnand", {{21, 5, NUM}, {16, 5, NUM}, {11, 5, NUM}}},
    {0x4c000042, "crnor", {{21, 5, NUM}, {16, 5, NUM}, {11, 5, NUM}}},
    {0x4c000382, "cror", {{21, 5, NUM}, {16, 5, NUM}, {11, 5, NUM}}},
    {0x4c000342, "crorc", {{21, 5, NUM}, {16, 5, NUM}, {11, 5, NUM}}},
    {0x4c000182, "crxor", {{21, 5, NUM}, {16, 5, NUM}, {11, 5, NUM}}},

    {0x7c0003d2, "divd", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c0003d3, "divd.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c0007d2, "divdo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c0007d3, "divdo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x7c000392, "divdu", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c000393, "divdu.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c000792, "divduo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c000793, "divduo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x7c0003d6, "divw", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0003d7, "divw.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0007d6, "divwo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0007d7, "divwo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000396, "divwu", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000397, "divwu.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000796, "divwuo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000797, "divwuo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000238, "eqv", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000239, "eqv.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    {0x7c000774, "extsb", {{16, 5, GREG}, {21, 5, GREG}}},
    {0x7c000775, "extsb.", {{16, 5, GREG}, {21, 5, GREG}}},
    {0x7c000734, "extsh", {{16, 5, GREG}, {21, 5, GREG}}},
    {0x7c000735, "extsh.", {{16, 5, GREG}, {21, 5, GREG}}},
    {0x7c0007b4, "extsw", {{16, 5, GREG}, {21, 5, GREG}}, IMPL64},
    {0x7c0007b5, "extsw.", {{16, 5, GREG}, {21, 5, GREG}}, IMPL64},

    {0xfc00002a, "fadd", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc00002b, "fadd.", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xec00002a, "fadds", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xec00002b, "fadds.", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc000028, "fsub", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc000029, "fsub.", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xec000028, "fsubs", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xec000029, "fsubs.", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc000032, "fmul", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}}},
    {0xfc000033, "fmul.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}}},
    {0xec000032, "fmuls", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}}},
    {0xec000033, "fmuls.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}}},
    {0xfc000024, "fdiv", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc000025, "fdiv.", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xec000024, "fdivs", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xec000025, "fdivs.", {{21, 5, FREG}, {16, 5, FREG}, {11, 5, FREG}}},

    {0xfc00003a, "fmadd", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc00003b, "fmadd.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xec00003a, "fmadds", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xec00003b, "fmadds.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc000038, "fmsub", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc000039, "fmsub.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xec000038, "fmsubs", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xec000039, "fmsubs.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc00003e, "fnmadd", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc00003f, "fnmadd.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xec00003e, "fnmadds", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xec00003f, "fnmadds.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc00003c, "fnmsub", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc00003d, "fnmsub.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xec00003c, "fnmsubs", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xec00003d, "fnmsubs.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},

    {0xfc000090, "fmr", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000091, "fmr.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000210, "fabs", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000211, "fabs.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000050, "fneg", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000051, "fneg.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000110, "fnabs", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000111, "fnabs.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xec000030, "fres", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xec000031, "fres.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000018, "frsp", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000019, "frsp.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000034, "frsqrte", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc000035, "frsqrte.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc00002e, "fsel", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc00002f, "fsel.", {{21, 5, FREG}, {16, 5, FREG}, {6, 5, FREG}, {11, 5, FREG}}},
    {0xfc00002c, "fsqrt", {{21, 5, FREG}, {11, 5, FREG}}, OPTIONAL | CPU970},
    {0xfc00002d, "fsqrt.", {{21, 5, FREG}, {11, 5, FREG}}, OPTIONAL | CPU970},
    {0xec00002c, "fsqrts", {{21, 5, FREG}, {11, 5, FREG}}, OPTIONAL | CPU970},
    {0xec00002d, "fsqrts.", {{21, 5, FREG}, {11, 5, FREG}}, OPTIONAL | CPU970},
    {0xfc00065c, "fctid", {{21, 5, FREG}, {11, 5, FREG}}, IMPL64},
    {0xfc00065d, "fctid.", {{21, 5, FREG}, {11, 5, FREG}}, IMPL64},
    {0xfc00065e, "fctidz", {{21, 5, FREG}, {11, 5, FREG}}, IMPL64},
    {0xfc00065f, "fctidz.", {{21, 5, FREG}, {11, 5, FREG}}, IMPL64},
    {0xfc00001c, "fctiw", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc00001d, "fctiw.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc00001e, "fctiwz", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc00001f, "fctiwz.", {{21, 5, FREG}, {11, 5, FREG}}},
    {0xfc00069c, "fcfid", {{21, 5, FREG}, {11, 5, FREG}}, IMPL64},
    {0xfc00069d, "fcfid.", {{21, 5, FREG}, {11, 5, FREG}}, IMPL64},

    {0xfc000000, "fcmpu", {{21, 5, CRFONLY}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc000000, "fcmpu", {{23, 3, NUM}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc000040, "fcmpo", {{21, 5, CRFONLY}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc000040, "fcmpo", {{23, 3, NUM}, {16, 5, FREG}, {11, 5, FREG}}},
    {0xfc00048e, "mffs", {{21, 5, FREG}}},
    {0xfc00048f, "mffs.", {{21, 5, FREG}}},
    {0xfc000080, "mcrfs", {{21, 5, CRFONLY}, {18, 5, NUM}}},
    {0xfc000080, "mcrfs", {{23, 3, NUM}, {18, 5, NUM}}},
    {0xfc00010c, "mtfsfi", {{23, 3, NUM}, {12, 4, NUM}}},
    {0xfc00010d, "mtfsfi.", {{23, 3, NUM}, {12, 4, NUM}}},
    {0xfc00058e, "mtfsf", {{17, 8, NUM}, {11, 5, FREG}}},
    {0xfc00058f, "mtfsf.", {{17, 8, NUM}, {11, 5, FREG}}},
    {0xfc00008c, "mtfsb0", {{21, 5, NUM}}},
    {0xfc00008d, "mtfsb0.", {{21, 5, NUM}}},
    {0xfc00004c, "mtfsb1", {{21, 5, NUM}}},
    {0xfc00004d, "mtfsb1.", {{21, 5, NUM}}},

    {0x88000000, "lbz", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0x7c0000ae, "lbzx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x8c000000, "lbzu", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0x7c0000ee, "lbzux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0xa0000000, "lhz", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0x7c00022e, "lhzx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0xa4000000, "lhzu", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0x7c00026e, "lhzux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0xa8000000, "lha", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0x7c0002ae, "lhax", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0xac000000, "lhau", {{21, 5, GREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c0002ee, "lhaux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x80000000, "lwz", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0x7c00002e, "lwzx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x84000000, "lwzu", {{21, 5, GREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c00006e, "lwzux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0xe8000002, "lwa", {{21, 5, GREG}, {2, 14, DS}, {16, 5, G0REG}}, IMPL64},
    {0x7c0002aa, "lwax", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, IMPL64},
    {0x7c0002ea, "lwaux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0xe8000000, "ld", {{21, 5, GREG}, {2, 14, DS}, {16, 5, G0REG}}, IMPL64},
    {0x7c00002a, "ldx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, IMPL64},
    {0xe8000001, "ldu", {{21, 5, GREG}, {2, 14, DS}, {16, 5, GREG}}, IMPL64},
    {0x7c00006a, "ldux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0xb8000000, "lmw", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0xbc000000, "stmw", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},

    {0x7c00062c, "lhbrx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00042c, "lwbrx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00042a, "lswx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c000028, "lwarx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c0000a8, "ldarx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, IMPL64},

    {0x7c00022a, "lscbx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, CPU601},
    {0x7c00022b, "lscbx.", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, CPU601},

    {0x7c0004aa, "lswi", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, NUM0}}},

    {0xc0000000, "lfs", {{21, 5, FREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0xc4000000, "lfsu", {{21, 5, FREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c00042e, "lfsx", {{21, 5, FREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00046e, "lfsux", {{21, 5, FREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0xc8000000, "lfd", {{21, 5, FREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0xcc000000, "lfdu", {{21, 5, FREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c0004ae, "lfdx", {{21, 5, FREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c0004ee, "lfdux", {{21, 5, FREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x38000000, "la", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},

    {0x4c000000, "mcrf", {{21, 5, CRFONLY}, {16, 5, CRFONLY}}},
    {0x4c000000, "mcrf", {{23, 3, NUM}, {18, 3, NUM}}},

    {0x7c0002a6, "mfspr", {{21, 5, GREG}, {11, 10, SPREG}}},
    {0x7c0003a6, "mtspr", {{11, 10, SPREG}, {21, 5, GREG}}},
    {0x7c000120, "mtcrf", {{12, 8, FXM}, {21, 5, GREG}}},
    {0x7c000120, "mtocrf", {{12, 8, FXM}, {21, 5, GREG}}},
    {0x7c000400, "mcrxr", {{21, 5, CRFONLY}}},
    {0x7c000400, "mcrxr", {{23, 3, NUM}}},
    {0x7c000026, "mfcr", {{21, 5, GREG}}},
    {0x7c100026, "mfcr", {{21, 5, GREG}, {12, 8, FXM}}},
    {0x7c100026, "mfocrf", {{21, 5, GREG}, {12, 8, FXM}}},

    /* Move to/from spr mnemonics (assember extended mnemonics) */
    {0x7c0102a6, "mfxer", {{21, 5, GREG}}},
    {0x7c0802a6, "mflr", {{21, 5, GREG}}},
    {0x7c0902a6, "mfctr", {{21, 5, GREG}}},
    {0x7c0103a6, "mtxer", {{21, 5, GREG}}},
    {0x7c0803a6, "mtlr", {{21, 5, GREG}}},
    {0x7c0903a6, "mtctr", {{21, 5, GREG}}},
    {0x7c0002a6, "mfmq", {{21, 5, GREG}}},
    {0x7c0502a6, "mfrtcl", {{21, 5, GREG}}},
    {0x7c0402a6, "mfrtcu", {{21, 5, GREG}}},
    {0x7c0003a6, "mtmq", {{21, 5, GREG}}},
    {0x7c1503a6, "mtrtcl", {{21, 5, GREG}}},
    {0x7c1403a6, "mtrtcu", {{21, 5, GREG}}},

#ifdef NRW_COMPILER
    {0x7c0001d6, "mull", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0001d7, "mull.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0005d6, "mullo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0005d7, "mullo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
#endif /* NRW_COMPILER */
    {0x7c0001d6, "mullw", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0001d7, "mullw.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0005d6, "mullwo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c0005d7, "mullwo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000092, "mulhd", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c000093, "mulhd.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},

#ifdef NRW_COMPILER
    {0x7c000096, "mulwd", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000097, "mulwd.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
#endif /* NRW_COMPILER */
    {0x7c000096, "mulhw", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000097, "mulhw.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000012, "mulhdu", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c000013, "mulhdu.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x7c000016, "mulhwu", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000017, "mulhwu.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c0001d2, "mulld", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c0001d3, "mulld.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c0005d2, "mulldo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c0005d3, "mulldo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x7c0003b8, "nand", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c0003b9, "nand.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    {0x7c0000d0, "neg", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0000d1, "neg.", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0004d0, "nego", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0004d1, "nego.", {{21, 5, GREG}, {16, 5, GREG}}},

    {0x7c0000f8, "nor", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c0000f9, "nor.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    /* Miscellaneous mnemonics (assember extended mnemonics) */
    {
        0x60000000,
        "nop",
    },

    {0x60000000, "ori", {{16, 5, GREG}, {21, 5, GREG}, {0, 16, UI}}},
    {0x60000000, "ori", {{16, 5, ZERO}, {21, 5, ZERO}, {0, 16, ZERO}}},
    {0x64000000, "oris", {{16, 5, GREG}, {21, 5, GREG}, {0, 16, UI}}},
    {0x7c000378, "or", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000379, "or.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    /// @brief Move register
    {0x7c000378, "mr", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    {0x7c000338, "orc", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000339, "orc.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    {0x78000000, "rldicl", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}, {0, 0, mb}}, IMPL64},
    {0x78000001, "rldicl.", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}, {0, 0, mb}}, IMPL64},
    {0x78000004, "rldicr", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}, {0, 0, mb}}, IMPL64},
    {0x78000005, "rldicr.", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}, {0, 0, mb}}, IMPL64},
    {0x78000008, "rldic", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}, {0, 0, mb}}, IMPL64},
    {0x78000009, "rldic.", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}, {0, 0, mb}}, IMPL64},
    {0x7800000c, "rldimi", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}, {0, 0, mb}}, IMPL64},
    {0x7800000d, "rldimi.", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}, {0, 0, mb}}, IMPL64},
    {0x78000010, "rldcl", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}, {0, 0, mb}}, IMPL64},
    {0x78000011, "rldcl.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}, {0, 0, mb}}, IMPL64},
    {0x78000012, "rldcr", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}, {0, 0, mb}}, IMPL64},
    {0x78000013, "rldcr.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}, {0, 0, mb}}, IMPL64},

    {0x54000000, "rlwinm", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM0}, {6, 5, MBE}, {1, 5, MBE}}},
    {0x54000001,
     "rlwinm.",
     {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM0}, {6, 5, MBE}, {1, 5, MBE}}},
    {0x5c000000, "rlwnm", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}, {6, 5, MBE}, {1, 5, MBE}}},
    {0x5c000001, "rlwnm.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}, {6, 5, MBE}, {1, 5, MBE}}},
    {0x50000000, "rlwimi", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM0}, {6, 5, MBE}, {1, 5, MBE}}},
    {0x50000001,
     "rlwimi.",
     {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM0}, {6, 5, MBE}, {1, 5, MBE}}},

    {
        0x44000002,
        "sc",
    },
    {0x4c000024, "rfid", {{0}}, IMPL64 | OPTIONAL},

    {0x7c000030, "slw", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000031, "slw.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000036, "sld", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c000037, "sld.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x7c000430, "srw", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000431, "srw.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000436, "srd", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c000437, "srd.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x7c000670, "srawi", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}},
    {0x7c000671, "srawi.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}},
    {0x7c000674, "sradi", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}}, IMPL64},
    {0x7c000675, "sradi.", {{16, 5, GREG}, {21, 5, GREG}, {0, 0, sh}}, IMPL64},

    {0x7c000630, "sraw", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000631, "sraw.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000634, "srad", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c000635, "srad.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x98000000, "stb", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0x9c000000, "stbu", {{21, 5, GREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c0001ae, "stbx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c0001ee, "stbux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0xb0000000, "sth", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0xb4000000, "sthu", {{21, 5, GREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c00032e, "sthx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00036e, "sthux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x90000000, "stw", {{21, 5, GREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0x94000000, "stwu", {{21, 5, GREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c00012e, "stwx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00016e, "stwux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0xf8000000, "std", {{21, 5, GREG}, {2, 14, DS}, {16, 5, G0REG}}, IMPL64},
    {0xf8000001, "stdu", {{21, 5, GREG}, {2, 14, DS}, {16, 5, GREG}}, IMPL64},
    {0x7c00012a, "stdx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, IMPL64},
    {0x7c00016a, "stdux", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x7c00072c, "sthbrx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00052c, "stwbrx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00052a, "stswx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00012d, "stwcx.", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c0001ad, "stdcx.", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, IMPL64},

    {0x7c0005aa, "stswi", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, NUM0}}},

    {
        0x7c0007ae,
        "stfiwx",
        {{21, 5, FREG}, {16, 5, G0REG}, {11, 5, GREG}},
    },

    {0xd0000000, "stfs", {{21, 5, FREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0xd4000000, "stfsu", {{21, 5, FREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c00052e, "stfsx", {{21, 5, FREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00056e, "stfsux", {{21, 5, FREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0xd8000000, "stfd", {{21, 5, FREG}, {0, 16, D}, {16, 5, G0REG}}},
    {0xdc000000, "stfdu", {{21, 5, FREG}, {0, 16, D}, {16, 5, GREG}}},
    {0x7c0005ae, "stfdx", {{21, 5, FREG}, {16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c0005ee, "stfdux", {{21, 5, FREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x20000000, "subfic", {{21, 5, GREG}, {16, 5, GREG}, {0, 16, SI}}},
    {0x7c000050, "sub", {{21, 5, GREG}, {11, 5, GREG}, {16, 5, GREG}}},
    {0x7c000051, "sub.", {{21, 5, GREG}, {11, 5, GREG}, {16, 5, GREG}}},
    {0x7c000450, "subo", {{21, 5, GREG}, {11, 5, GREG}, {16, 5, GREG}}},
    {0x7c000451, "subo.", {{21, 5, GREG}, {11, 5, GREG}, {16, 5, GREG}}},
    {0x7c000050, "subf", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000051, "subf.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000450, "subfo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000451, "subfo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000010, "subc", {{21, 5, GREG}, {11, 5, GREG}, {16, 5, GREG}}},
    {0x7c000011, "subc.", {{21, 5, GREG}, {11, 5, GREG}, {16, 5, GREG}}},
    {0x7c000410, "subco", {{21, 5, GREG}, {11, 5, GREG}, {16, 5, GREG}}},
    {0x7c000411, "subco.", {{21, 5, GREG}, {11, 5, GREG}, {16, 5, GREG}}},
    {0x7c000010, "subfc", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000011, "subfc.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000410, "subfco", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000411, "subfco.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c000110, "subfe", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000111, "subfe.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000510, "subfeo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000511, "subfeo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}},

    {0x7c0001d0, "subfme", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0001d1, "subfme.", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0005d0, "subfmeo", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c0005d1, "subfmeo.", {{21, 5, GREG}, {16, 5, GREG}}},

    {0x7c000190, "subfze", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c000191, "subfze.", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c000590, "subfzeo", {{21, 5, GREG}, {16, 5, GREG}}},
    {0x7c000591, "subfzeo.", {{21, 5, GREG}, {16, 5, GREG}}},

    {
        0x7c0004ac,
        "sync",
    },
    {0x7c0004ac, "sync", {{21, 2, NUM}}},
    {
        0x7c2004ac,
        "lwsync",
    },
    {
        0x7c4004ac,
        "ptesync",
    },

    {0x08000000, "tdi", {{21, 5, NUM}, {16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x0a000000, "tdlti", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x0a800000, "tdlei", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x08800000, "tdeqi", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x09800000, "tdgei", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x09000000, "tdgti", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x09800000, "tdnli", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x0b000000, "tdnei", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x0a800000, "tdngi", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x08400000, "tdllti", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x08c00000, "tdllei", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x08a00000, "tdlgei", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x08200000, "tdlgti", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x08a00000, "tdlnli", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},
    {0x08c00000, "tdlngi", {{16, 5, GREG}, {0, 16, SI}}, IMPL64},

    {0x7c000088, "td", {{21, 5, NUM}, {16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7e000088, "tdlt", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7e800088, "tdle", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c800088, "tdeq", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7d800088, "tdge", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7d000088, "tdgt", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7d800088, "tdnl", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7f000088, "tdne", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7e800088, "tdng", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c400088, "tdllt", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7cc00088, "tdlle", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7ca00088, "tdlge", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7c200088, "tdlgt", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7ca00088, "tdlnl", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},
    {0x7cc00088, "tdlng", {{16, 5, GREG}, {11, 5, GREG}}, IMPL64},

    {0x0c000000, "twi", {{21, 5, NUM}, {16, 5, GREG}, {0, 16, SI}}},
    {0x0e000000, "twlti", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0e800000, "twlei", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0c800000, "tweqi", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0d800000, "twgei", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0d000000, "twgti", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0d800000, "twnli", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0f000000, "twnei", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0e800000, "twngi", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0c400000, "twllti", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0cc00000, "twllei", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0ca00000, "twlgei", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0c200000, "twlgti", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0ca00000, "twlnli", {{16, 5, GREG}, {0, 16, SI}}},
    {0x0cc00000, "twlngi", {{16, 5, GREG}, {0, 16, SI}}},

    {0x7c000008, "tw", {{21, 5, NUM}, {16, 5, GREG}, {11, 5, GREG}}},
    {0x7c000008, "tw", {{21, 5, NUM}, {16, 5, ZERO}, {11, 5, ZERO}}},
    {0x7e000008, "twlt", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7e800008, "twle", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7c800008, "tweq", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7d800008, "twge", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7d000008, "twgt", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7d800008, "twnl", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7f000008, "twne", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7e800008, "twng", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7c400008, "twllt", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7cc00008, "twlle", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7ca00008, "twlge", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7c200008, "twlgt", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7ca00008, "twlnl", {{16, 5, GREG}, {11, 5, GREG}}},
    {0x7cc00008, "twlng", {{16, 5, GREG}, {11, 5, GREG}}},
    {
        0x7fe00008,
        "trap",
    },

    {0x68000000, "xori", {{16, 5, GREG}, {21, 5, GREG}, {0, 16, UI}}},
    {0x6c000000, "xoris", {{16, 5, GREG}, {21, 5, GREG}, {0, 16, UI}}},
    {0x7c000278, "xor", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000279, "xor.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}},

    /* Cache Management Instructions (from book II) */
    {0x7c0007ac, "icbi", {{16, 5, G0REG}, {11, 5, GREG}}},
    {
        0x4c00012c,
        "isync",
    },
    {0x7c00022c, "dcbt", {{16, 5, G0REG}, {11, 5, GREG}}},
    {
        0x7c00022c,
        "dcbt",
        {{16, 5, G0REG}, {11, 5, GREG}, {21, 4, NUM}},
    },
    {0x7c0001ec, "dcbtst", {{16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00022c, "dcbt128", {{16, 5, G0REG}, {11, 5, GREG}, {21, 4, NUM}}, IMPL64 | OPTIONAL},
    {0x7c0007ec, "dcbz", {{16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c2007ec, "dcbzl", {{16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c2007ec, "dcbz128", {{16, 5, G0REG}, {11, 5, GREG}}, IMPL64 | OPTIONAL},
    {0x7c00006c, "dcbst", {{16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c0000ac, "dcbf", {{16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c00026c, "eciwx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, OPTIONAL | CPU970},
    {0x7c00036c, "ecowx", {{21, 5, GREG}, {16, 5, G0REG}, {11, 5, GREG}}, OPTIONAL | CPU970},
    {
        0x7c0006ac,
        "eieio",
    },
    /* Instructions (from book III) */
    {
        0x4c000064,
        "rfi",
    },
    {0x7c000124, "mtmsr", {{21, 5, GREG}}},
    {0x7c000164, "mtmsrd", {{21, 5, GREG}}, IMPL64 | OPTIONAL},
    {0x7c000164, "mtmsrd", {{21, 5, GREG}, {16, 1, NUM}}, IMPL64 | OPTIONAL},
    {0x7c0000a6, "mfmsr", {{21, 5, GREG}}},
    {0x7c0005ec, "dcba", {{16, 5, G0REG}, {11, 5, GREG}}, OPTIONAL},
    {0x7c0003ac, "dcbi", {{16, 5, G0REG}, {11, 5, GREG}}},
    {0x7c0001a4, "mtsr", {{16, 4, SGREG}, {21, 5, GREG}}},
    {0x7c0004a6, "mfsr", {{21, 5, GREG}, {16, 4, SGREG}}},
    {0x7c0001e4, "mtsrin", {{21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000526, "mfsrin", {{21, 5, GREG}, {11, 5, GREG}}},
    {0x7c000364, "slbie", {{11, 5, GREG}}, IMPL64 | OPTIONAL},
    {0x7c0003e4, "slbia", {{0}}, IMPL64 | OPTIONAL},
    {0x7c000324, "slbmte", {{21, 5, GREG}, {11, 5, GREG}}, IMPL64 | OPTIONAL},
    {0x7c0006a6, "slbmfev", {{21, 5, GREG}, {11, 5, GREG}}, IMPL64 | OPTIONAL},
    {0x7c000726, "slbmfee", {{21, 5, GREG}, {11, 5, GREG}}, IMPL64 | OPTIONAL},
    {0x7c000264, "tlbie", {{11, 5, GREG}}, OPTIONAL | CPU970},
    {0x7c000264, "tlbie", {{11, 5, GREG}, {21, 1, NUM}}, IMPL64 | OPTIONAL | CPU970},
    {0x7c000224, "tlbiel", {{11, 5, GREG}}, IMPL64 | OPTIONAL},
    {0x7c0002e4, "tlbia", {{0}}, OPTIONAL | CPU970},
    {0x7c00046c, "tlbsync", {{0}}, OPTIONAL | CPU970},
    {0x7c1c43a6, "mttbl", {{21, 5, GREG}}},
    {0x7c1d43a6, "mttbu", {{21, 5, GREG}}},
    {0x7c0002e6, "mftb", {{21, 5, GREG}, {11, 10, SPREG}}},
    {0x7c0c42e6, "mftb", {{21, 5, GREG}}},
    {0x7c0d42e6, "mftbu", {{21, 5, GREG}}},
    {0x00000200, "attn", {{11, 15, NUM}}, OPTIONAL | CPU970},

    /* Instructions (from book IV) */
    {0x24000000, "dozi", {{21, 5, GREG}, {16, 5, GREG}, {0, 16, SI}}, CPU601},
    {0x7c000210, "doz", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000211, "doz.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000610, "dozo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000611, "dozo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c0002d0, "abs", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},
    {0x7c0002d1, "abs.", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},
    {0x7c0006d0, "abso", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},
    {0x7c0006d1, "abso.", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},

    {0x7c0003d0, "nabs", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},
    {0x7c0003d1, "nabs.", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},
    {0x7c0007d0, "nabso", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},
    {0x7c0007d1, "nabso.", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},

    {0x1c000000, "mulli", {{21, 5, GREG}, {16, 5, GREG}, {0, 16, SI}}},

    {0x7c0000d6, "mul", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0000d7, "mul.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0004d6, "mulo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0004d7, "mulo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c000296, "div", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000297, "div.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000696, "divo", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000697, "divo.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c0002d6, "divs", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0002d7, "divs.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0006d6, "divso", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0006d7, "divso.", {{21, 5, GREG}, {16, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x58000000,
     "rlmi",
     {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}, {6, 5, MBE}, {1, 5, MBE}},
     CPU601},
    {0x58000001,
     "rlmi.",
     {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}, {6, 5, MBE}, {1, 5, MBE}},
     CPU601},

    {0x7c000432, "rrib", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000433, "rrib.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c00003a, "maskg", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c00003b, "maskg.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c00043a, "maskir", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c00043b, "maskir.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c000130, "slq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000131, "slq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c000530, "srq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000531, "srq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c000170, "sliq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},
    {0x7c000171, "sliq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},

    {0x7c000570, "sriq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},
    {0x7c000571, "sriq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},

    {0x7c0001f0, "slliq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},
    {0x7c0001f1, "slliq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},

    {0x7c0005f0, "srliq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},
    {0x7c0005f1, "srliq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},

    {0x7c0001b0, "sllq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0001b1, "sllq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c0005b0, "srlq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0005b1, "srlq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c000132, "sle", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000133, "sle.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c000532, "sre", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000533, "sre.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c0001b2, "sleq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0001b3, "sleq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c0005b2, "sreq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c0005b3, "sreq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c000770, "sraiq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},
    {0x7c000771, "sraiq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, NUM}}, CPU601},

    {0x7c000730, "sraq", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000731, "sraq.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    {0x7c000732, "srea", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},
    {0x7c000733, "srea.", {{16, 5, GREG}, {21, 5, GREG}, {11, 5, GREG}}, CPU601},

    /* Added from the POWER 601 book */
    {0x7c000426, "clcs", {{21, 5, GREG}, {16, 5, GREG}}, CPU601},

    /* Added from the POWER 603 book.
     * These are really 603 specific instructions but we mark them as OPTIONAL
     * so that the -force_cpusubtype_ALL flag as to be used.  This makes it so
     * only 601 instructions will cause the cputype to be set to other an ALL.
     */
    {0x7c0007a4, "tlbld", {{11, 5, GREG}}, OPTIONAL},
    {0x7c0007e4, "tlbli", {{11, 5, GREG}}, OPTIONAL},

    /* VMX Instructions */
    {0x7c00000e, "lvebx", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c00004e, "lvehx", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c00008e, "lvewx", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c0000ce, "lvx", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c0002ce, "lvxl", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},

    {0x7c00010e, "stvebx", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c00014e, "stvehx", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c00018e, "stvewx", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c0001ce, "stvx", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c0003ce, "stvxl", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},

    {0x7c00000c, "lvsl", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},
    {0x7c00004c, "lvsr", {{21, 5, VREG}, {16, 5, G0REG}, {11, 5, GREG}}, VMX},

    {0x10000644, "mtvscr", {{11, 5, VREG}}, VMX},
    {0x10000604, "mfvscr", {{21, 5, VREG}}, VMX},

    {0x7c0002ac, "dst", {{16, 5, GREG}, {11, 5, GREG}, {21, 2, NUM}}, VMX},
    {0x7e0002ac, "dstt", {{16, 5, GREG}, {11, 5, GREG}, {21, 2, NUM}}, VMX},
    {0x7c0002ec, "dstst", {{16, 5, GREG}, {11, 5, GREG}, {21, 2, NUM}}, VMX},
    {0x7e0002ec, "dststt", {{16, 5, GREG}, {11, 5, GREG}, {21, 2, NUM}}, VMX},
    {0x7c00066c, "dss", {{21, 2, NUM}}, VMX},
    {0x7e00066c, "dssall", {{0}}, VMX},

    {0x10000000, "vaddubm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000200, "vaddubs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000300, "vaddsbs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000040, "vadduhm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000240, "vadduhs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000340, "vaddshs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000080, "vadduwm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000280, "vadduws", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000380, "vaddsws", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000000a, "vaddfp", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000180, "vaddcuw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000400, "vsububm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000600, "vsububs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000700, "vsubsbs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000440, "vsubuhm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000640, "vsubuhs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000740, "vsubshs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000480, "vsubuwm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000680, "vsubuws", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000780, "vsubsws", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000004a, "vsubfp", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000580, "vsubcuw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000008, "vmuloub", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000108, "vmulosb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000048, "vmulouh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000148, "vmulosh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000208, "vmuleub", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000308, "vmulesb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000248, "vmuleuh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000348, "vmulesh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000020, "vmhaddshs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},
    {0x10000021, "vmhraddshs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},
    {0x10000022, "vmladduhm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},
    {0x1000002e, "vmaddfp", {{21, 5, VREG}, {16, 5, VREG}, {6, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000024, "vmsumubm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},
    {0x10000025, "vmsummbm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},
    {0x10000026, "vmsumuhm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},
    {0x10000027, "vmsumuhs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},
    {0x10000028, "vmsumshm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},
    {0x10000029, "vmsumshs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},

    {0x10000788, "vsumsws", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000688, "vsum2sws", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000608, "vsum4ubs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000708, "vsum4sbs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000648, "vsum4shs", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000402, "vavgub", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000442, "vavguh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000482, "vavguw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000502, "vavgsb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000542, "vavgsh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000582, "vavgsw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000404, "vand", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000484, "vor", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100004c4, "vxor", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000444, "vandc", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000504, "vnor", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000004, "vrlb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000044, "vrlh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000084, "vrlw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000104, "vslb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000144, "vslh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000184, "vslw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100001c4, "vsl", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000204, "vsrb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000304, "vsrab", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000244, "vsrh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000344, "vsrah", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000284, "vsrw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000384, "vsraw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100002c4, "vsr", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000206, "vcmpgtub", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000606, "vcmpgtub.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000306, "vcmpgtsb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000706, "vcmpgtsb.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000246, "vcmpgtuh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000646, "vcmpgtuh.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000346, "vcmpgtsh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000746, "vcmpgtsh.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000286, "vcmpgtuw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000686, "vcmpgtuw.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000386, "vcmpgtsw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000786, "vcmpgtsw.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100002c6, "vcmpgtfp", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100006c6, "vcmpgtfp.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000006, "vcmpequb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000406, "vcmpequb.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000046, "vcmpequh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000446, "vcmpequh.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000086, "vcmpequw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000486, "vcmpequw.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100000c6, "vcmpeqfp", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100004c6, "vcmpeqfp.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x100001c6, "vcmpgefp", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100005c6, "vcmpgefp.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x100003c6, "vcmpbfp", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100007c6, "vcmpbfp.", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000002a, "vsel", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},

    {0x1000000e, "vpkuhum", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000008e, "vpkuhus", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000010e, "vpkshus", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000018e, "vpkshss", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000004e, "vpkuwum", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100000ce, "vpkuwus", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000014e, "vpkswus", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100001ce, "vpkswss", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000030e, "vpkpx", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000020e, "vupkhsb", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000024e, "vupkhsh", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000034e, "vupkhpx", {{21, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000028e, "vupklsb", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100002ce, "vupklsh", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100003ce, "vupklpx", {{21, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000000c, "vmrghb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000004c, "vmrghh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000008c, "vmrghw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000010c, "vmrglb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000014c, "vmrglh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000018c, "vmrglw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000020c, "vspltb", {{21, 5, VREG}, {11, 5, VREG}, {16, 5, NUM}}, VMX},
    {0x1000024c, "vsplth", {{21, 5, VREG}, {11, 5, VREG}, {16, 5, NUM}}, VMX},
    {0x1000028c, "vspltw", {{21, 5, VREG}, {11, 5, VREG}, {16, 5, NUM}}, VMX},

    {0x1000030c, "vspltisb", {{21, 5, VREG}, {16, 5, SNUM}}, VMX},
    {0x1000034c, "vspltish", {{21, 5, VREG}, {16, 5, SNUM}}, VMX},
    {0x1000038c, "vspltisw", {{21, 5, VREG}, {16, 5, SNUM}}, VMX},

    {0x1000002b, "vperm", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 5, VREG}}, VMX},

    {0x1000002c, "vsldoi", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}, {6, 4, NUM}}, VMX},

    {0x1000040c, "vslo", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000044c, "vsro", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000002, "vmaxub", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000102, "vmaxsb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000042, "vmaxuh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000142, "vmaxsh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000082, "vmaxuw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000182, "vmaxsw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000040a, "vmaxfp", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x10000202, "vminub", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000302, "vminsb", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000242, "vminuh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000342, "vminsh", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000282, "vminuw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x10000382, "vminsw", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000044a, "vminfp", {{21, 5, VREG}, {16, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000010a, "vrefp", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000014a, "vrsqrtefp", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100001ca, "vlogefp", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000018a, "vexptefp", {{21, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000002f, "vnmsubfp", {{21, 5, VREG}, {16, 5, VREG}, {6, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000020a, "vrfin", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000024a, "vrfiz", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x1000028a, "vrfip", {{21, 5, VREG}, {11, 5, VREG}}, VMX},
    {0x100002ca, "vrfim", {{21, 5, VREG}, {11, 5, VREG}}, VMX},

    {0x1000038a, "vctuxs", {{21, 5, VREG}, {11, 5, VREG}, {16, 5, NUM}}, VMX},
    {0x100003ca, "vctsxs", {{21, 5, VREG}, {11, 5, VREG}, {16, 5, NUM}}, VMX},

    {0x1000030a, "vcfux", {{21, 5, VREG}, {11, 5, VREG}, {16, 5, NUM}}, VMX},
    {0x1000034a, "vcfsx", {{21, 5, VREG}, {11, 5, VREG}, {16, 5, NUM}}, VMX},

    {0, ""} /* end of table marker */
};

#define kAsmFloatZeroRegister 0
#define kAsmZeroRegister 0

#define kAsmRegisterPrefix "r"
#define kAsmRegisterLimit 31
#define kAsmPcRegister 17
#define kAsmCrRegister 18
#define kAsmSpRegister 5

/* return address register */
#define kAsmRetRegister 19
