#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inst {char* i_name; int i_size; int i_mode; struct inst* i_extra; scalar_t__ i_has_modrm; } ;
struct i_addr {int dummy; } ;
typedef  int db_addr_t ;

/* Variables and functions */
#define  A 159 
#define  BX 158 
 int BYTE ; 
#define  CL 157 
#define  CR 156 
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  DB_STGY_XTRN ; 
#define  DI 155 
#define  DR 154 
#define  DX 153 
#define  Db 152 
#define  Dl 151 
#define  E 150 
#define  Eb 149 
#define  Eind 148 
#define  El 147 
#define  Ew 146 
 int FALSE ; 
#define  I 145 
#define  Ib 144 
#define  Iba 143 
#define  Ibs 142 
#define  Is 141 
#define  Iw 140 
 int LONG ; 
 int NONE ; 
#define  O 139 
#define  OS 138 
#define  R 137 
#define  Ri 136 
#define  Ril 135 
#define  Rw 134 
#define  S 133 
 int SDEP ; 
#define  SI 132 
#define  Si 131 
#define  TR 130 
 int TRUE ; 
 int WORD ; 
 struct inst* db_Grp1 ; 
 struct inst* db_Grp15 ; 
 char** db_Grp15b ; 
 struct inst* db_Grp2 ; 
 struct inst* db_Grp3 ; 
 struct inst* db_Grp4 ; 
 struct inst* db_Grp5 ; 
 struct inst* db_Grp6 ; 
 struct inst* db_Grp7 ; 
 struct inst* db_Grp8 ; 
 struct inst* db_Grp9 ; 
 struct inst db_bad_inst ; 
 int db_disasm_esc (int,int,int,int,char const*) ; 
 struct inst** db_inst_0f ; 
 struct inst* db_inst_table ; 
 int* db_lengths ; 
 int /*<<< orphan*/  db_print_address (char const*,int,struct i_addr*) ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (int,int /*<<< orphan*/ ) ; 
 int db_read_address (int,int,int,struct i_addr*) ; 
 int /*<<< orphan*/ ** db_reg ; 
 int /*<<< orphan*/ * db_seg_reg ; 
 int db_segsize (int /*<<< orphan*/ ) ; 
 int f_mod (int) ; 
 size_t f_reg (int) ; 
 size_t f_rm (int) ; 
 int /*<<< orphan*/  get_value_inc (int,int,int,int) ; 
 int /*<<< orphan*/  kdb_frame ; 
#define  o1 129 
#define  o3 128 

db_addr_t
db_disasm(db_addr_t loc, bool altfmt)
{
	int	inst;
	int	size;
	int	short_addr;
	const char *	seg;
	const struct inst *	ip;
	const char *	i_name;
	int	i_size;
	int	i_mode;
	int	regmodrm = 0;
	bool	first;
	int	displ;
	int	prefix;
	int	rep;
	int	imm;
	int	imm2;
	int	len;
	struct i_addr	address;

	if (db_segsize(kdb_frame) == 16)
	   altfmt = !altfmt;
	get_value_inc(inst, loc, 1, FALSE);
	if (altfmt) {
	    short_addr = TRUE;
	    size = WORD;
	}
	else {
	    short_addr = FALSE;
	    size = LONG;
	}
	seg = NULL;

	/*
	 * Get prefixes
	 */
	rep = FALSE;
	prefix = TRUE;
	do {
	    switch (inst) {
		case 0x66:
		    size = (altfmt ? LONG : WORD);
		    break;
		case 0x67:
		    short_addr = !altfmt;
		    break;
		case 0x26:
		    seg = "%es";
		    break;
		case 0x36:
		    seg = "%ss";
		    break;
		case 0x2e:
		    seg = "%cs";
		    break;
		case 0x3e:
		    seg = "%ds";
		    break;
		case 0x64:
		    seg = "%fs";
		    break;
		case 0x65:
		    seg = "%gs";
		    break;
		case 0xf0:
		    db_printf("lock ");
		    break;
		case 0xf2:
		    db_printf("repne ");
		    break;
		case 0xf3:
		    rep = TRUE;
		    break;
		default:
		    prefix = FALSE;
		    break;
	    }
	    if (prefix) {
		get_value_inc(inst, loc, 1, FALSE);
	    }
	    if (rep == TRUE) {
		if (inst == 0x90) {
		    db_printf("pause\n");
		    return (loc);
		}
		db_printf("repe ");	/* XXX repe VS rep */
		rep = FALSE;
	    }
	} while (prefix);

	if (inst >= 0xd8 && inst <= 0xdf) {
	    loc = db_disasm_esc(loc, inst, short_addr, size, seg);
	    db_printf("\n");
	    return (loc);
	}

	if (inst == 0x0f) {
	    get_value_inc(inst, loc, 1, FALSE);
	    ip = db_inst_0f[inst>>4];
	    if (ip == NULL) {
		ip = &db_bad_inst;
	    }
	    else {
		ip = &ip[inst&0xf];
	    }
	}
	else
	    ip = &db_inst_table[inst];

	if (ip->i_has_modrm) {
	    get_value_inc(regmodrm, loc, 1, FALSE);
	    loc = db_read_address(loc, short_addr, regmodrm, &address);
	}

	i_name = ip->i_name;
	i_size = ip->i_size;
	i_mode = ip->i_mode;

	if (ip->i_extra == db_Grp1 || ip->i_extra == db_Grp2 ||
	    ip->i_extra == db_Grp6 || ip->i_extra == db_Grp7 ||
	    ip->i_extra == db_Grp8 || ip->i_extra == db_Grp9 ||
	    ip->i_extra == db_Grp15) {
	    i_name = ((const char * const *)ip->i_extra)[f_reg(regmodrm)];
	}
	else if (ip->i_extra == db_Grp3) {
	    ip = ip->i_extra;
	    ip = &ip[f_reg(regmodrm)];
	    i_name = ip->i_name;
	    i_mode = ip->i_mode;
	}
	else if (ip->i_extra == db_Grp4 || ip->i_extra == db_Grp5) {
	    ip = ip->i_extra;
	    ip = &ip[f_reg(regmodrm)];
	    i_name = ip->i_name;
	    i_mode = ip->i_mode;
	    i_size = ip->i_size;
	}

	/* Special cases that don't fit well in the tables. */
	if (ip->i_extra == db_Grp7 && f_mod(regmodrm) == 3) {
		switch (regmodrm) {
		case 0xc8:
			i_name = "monitor";
			i_size = NONE;
			i_mode = 0;
			break;
		case 0xc9:
			i_name = "mwait";
			i_size = NONE;
			i_mode = 0;
			break;
		}
	}
	if (ip->i_extra == db_Grp15 && f_mod(regmodrm) == 3) {
		i_name = db_Grp15b[f_reg(regmodrm)];
		i_size = NONE;
		i_mode = 0;
	}

	if (i_size == SDEP) {
	    if (size == WORD)
		db_printf("%s", i_name);
	    else
		db_printf("%s", (const char *)ip->i_extra);
	}
	else {
	    db_printf("%s", i_name);
	    if (i_size != NONE) {
		if (i_size == BYTE) {
		    db_printf("b");
		    size = BYTE;
		}
		else if (i_size == WORD) {
		    db_printf("w");
		    size = WORD;
		}
		else if (size == WORD)
		    db_printf("w");
		else
		    db_printf("l");
	    }
	}
	db_printf("\t");
	for (first = true;
	     i_mode != 0;
	     i_mode >>= 8, first = false)
	{
	    if (!first)
		db_printf(",");

	    switch (i_mode & 0xFF) {

		case E:
		    db_print_address(seg, size, &address);
		    break;

		case Eind:
		    db_printf("*");
		    db_print_address(seg, size, &address);
		    break;

		case El:
		    db_print_address(seg, LONG, &address);
		    break;

		case Ew:
		    db_print_address(seg, WORD, &address);
		    break;

		case Eb:
		    db_print_address(seg, BYTE, &address);
		    break;

		case R:
		    db_printf("%s", db_reg[size][f_reg(regmodrm)]);
		    break;

		case Rw:
		    db_printf("%s", db_reg[WORD][f_reg(regmodrm)]);
		    break;

		case Ri:
		    db_printf("%s", db_reg[size][f_rm(inst)]);
		    break;

		case Ril:
		    db_printf("%s", db_reg[LONG][f_rm(inst)]);
		    break;

		case S:
		    db_printf("%s", db_seg_reg[f_reg(regmodrm)]);
		    break;

		case Si:
		    db_printf("%s", db_seg_reg[f_reg(inst)]);
		    break;

		case A:
		    db_printf("%s", db_reg[size][0]);	/* acc */
		    break;

		case BX:
		    if (seg)
			db_printf("%s:", seg);
		    db_printf("(%s)", short_addr ? "%bx" : "%ebx");
		    break;

		case CL:
		    db_printf("%%cl");
		    break;

		case DX:
		    db_printf("%%dx");
		    break;

		case SI:
		    if (seg)
			db_printf("%s:", seg);
		    db_printf("(%s)", short_addr ? "%si" : "%esi");
		    break;

		case DI:
		    db_printf("%%es:(%s)", short_addr ? "%di" : "%edi");
		    break;

		case CR:
		    db_printf("%%cr%d", f_reg(regmodrm));
		    break;

		case DR:
		    db_printf("%%dr%d", f_reg(regmodrm));
		    break;

		case TR:
		    db_printf("%%tr%d", f_reg(regmodrm));
		    break;

		case I:
		    len = db_lengths[size];
		    get_value_inc(imm, loc, len, FALSE);
		    db_printf("$%#r", imm);
		    break;

		case Is:
		    len = db_lengths[size];
		    get_value_inc(imm, loc, len, FALSE);
		    db_printf("$%+#r", imm);
		    break;

		case Ib:
		    get_value_inc(imm, loc, 1, FALSE);
		    db_printf("$%#r", imm);
		    break;

		case Iba:
		    get_value_inc(imm, loc, 1, FALSE);
		    if (imm != 0x0a)
			db_printf("$%#r", imm);
		    break;

		case Ibs:
		    get_value_inc(imm, loc, 1, TRUE);
		    if (size == WORD)
			imm &= 0xFFFF;
		    db_printf("$%+#r", imm);
		    break;

		case Iw:
		    get_value_inc(imm, loc, 2, FALSE);
		    db_printf("$%#r", imm);
		    break;

		case O:
		    len = (short_addr ? 2 : 4);
		    get_value_inc(displ, loc, len, FALSE);
		    if (seg)
			db_printf("%s:%+#r",seg, displ);
		    else
			db_printsym((db_addr_t)displ, DB_STGY_ANY);
		    break;

		case Db:
		    get_value_inc(displ, loc, 1, TRUE);
		    displ += loc;
		    if (size == WORD)
			displ &= 0xFFFF;
		    db_printsym((db_addr_t)displ, DB_STGY_XTRN);
		    break;

		case Dl:
		    len = db_lengths[size];
		    get_value_inc(displ, loc, len, FALSE);
		    displ += loc;
		    if (size == WORD)
			displ &= 0xFFFF;
		    db_printsym((db_addr_t)displ, DB_STGY_XTRN);
		    break;

		case o1:
		    db_printf("$1");
		    break;

		case o3:
		    db_printf("$3");
		    break;

		case OS:
		    len = db_lengths[size];
		    get_value_inc(imm, loc, len, FALSE);	/* offset */
		    get_value_inc(imm2, loc, 2, FALSE);	/* segment */
		    db_printf("$%#r,%#r", imm2, imm);
		    break;
	    }
	}
	db_printf("\n");
	return (loc);
}