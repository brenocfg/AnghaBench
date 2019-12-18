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
struct sparc_insn {unsigned int match; char* format; scalar_t__ name; } ;
typedef  int int64_t ;
typedef  scalar_t__ db_addr_t ;

/* Variables and functions */
 unsigned int COND2 (int,int) ; 
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  DB_STGY_PROC ; 
 unsigned int EIF_F2_A (int) ; 
 unsigned int EIF_F2_COND (int) ; 
 unsigned int EIF_F2_P (int) ; 
 unsigned int EIF_F3_OPF (int) ; 
 unsigned int EIF_F3_X (int) ; 
 unsigned int EIF_F4_TCOND (int) ; 
 unsigned int FORMAT2 (int,int) ; 
 unsigned int FORMAT3 (int,int,int) ; 
 int IF_SIMM (unsigned int,int) ; 
 int /*<<< orphan*/  SIGN (int) ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/ * ccodes ; 
 unsigned int db_get_value (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * prefetch ; 
 int /*<<< orphan*/ * priv_regs ; 
 int /*<<< orphan*/ * regs ; 
 int /*<<< orphan*/  sparc_i ; 
 int /*<<< orphan*/ * state_regs ; 

db_addr_t
db_disasm(db_addr_t loc, bool altfmt)
{
	const struct sparc_insn* i_ptr = (struct sparc_insn *)&sparc_i;
	unsigned int insn, you_lose, bitmask;
	int matchp;
	const char* f_ptr, *cp;

	you_lose = 0;
	matchp = 0;
	insn = db_get_value(loc, 4, 0);

	if (insn == 0x01000000) {
		db_printf("nop\n");
		return loc + 4;
	}

	while (i_ptr->name) {
		/* calculate YOU_LOSE value */
		bitmask= (i_ptr->match);
		you_lose = (~bitmask);

		if (((bitmask>>30) & 0x3) == 0x1) {
			/* Call */
			you_lose = ((~0x1)<<30);
		} else if (((bitmask>>30) & 0x3) == 0x0) {
			if (((bitmask>>22) & 0x7) == 0x4) {
				/* Sethi */
				you_lose &= (FORMAT2(0x3,0x7));
			} else {
				/* Branches */
				you_lose &= (FORMAT2(0x3,0x7) |
				    EIF_F2_COND(0xf));
			}
		} else if (((bitmask>>30) & 0x3) == 0x2 &&
			   ((bitmask>>19) & 0x3f) == 0x34) /* XXX */ {
			/* FPop1 */
			you_lose &= (FORMAT3(0x3,0x3f,0x1) |
			    EIF_F3_OPF(0x1ff));
		} else if (((bitmask>>30) & 0x3) == 0x2 &&
			   ((bitmask>>19) & 0x3f) == 0x3a) /* XXX */ {
			/* Tcc */
			you_lose &= (FORMAT3(0x3,0x3f,0x1) | EIF_F4_TCOND(0xf));
		} else if (((bitmask>>30) & 0x3) == 0x2 &&
			   ((bitmask>>21) & 0xf) == 0x9 &&
			   ((bitmask>>19) & 0x3) != 0) /* XXX */ {
			/* shifts */
			you_lose &= (FORMAT3(0x3,0x3f,0x1)) | EIF_F3_X(1);
		} else if (((bitmask>>30) & 0x3) == 0x2 &&
			   ((bitmask>>19) & 0x3f) == 0x2c) /* XXX */ {
			/* cmov */
			you_lose &= (FORMAT3(0x3,0x3f,0x1) | COND2(1,0xf));
		} else if (((bitmask>>30) & 0x3) == 0x2 &&
			   ((bitmask>>19) & 0x3f) == 0x35) /* XXX */ {
			/* fmov */
			you_lose &= (FORMAT3(0x3,0x3f,0x1) | COND2(1,0xf));
		} else {
			you_lose &= (FORMAT3(0x3,0x3f,0x1));
		}

		if (((bitmask & insn) == bitmask) && ((you_lose & insn) == 0)) {
			matchp = 1;
			break;
		}
		i_ptr++;
	}

	if (!matchp) {
		db_printf("undefined\n");
		return loc + 4;
	}

	db_printf("%s", i_ptr->name);

	f_ptr = i_ptr->format;

	for (cp = f_ptr; *cp; cp++) {
		if (*cp == ',') {
			for (;f_ptr < cp; f_ptr++)
				switch (*f_ptr) {
				case 'a':
					if (insn & EIF_F2_A(1))
						db_printf(",a");
					break;
				case 'p':
					if (insn & EIF_F2_P(1))
						db_printf(",pt");
					else
						db_printf(",pn");
					break;
				}
			f_ptr++;
			break;
		}
	}
	db_printf("      \t");

	while (*f_ptr) {
		switch (*f_ptr) {
			int64_t val;
		case '1':
			db_printf("%%%s", regs[((insn >> 14) & 0x1f)]);
			break;
		case '2':
			db_printf("%%%s", regs[(insn & 0x1f)]);
			break;
		case 'd':
			db_printf("%%%s", regs[((insn >> 25) & 0x1f)]);
			break;
		case '3':
			db_printf("%%f%d", ((insn >> 14) & 0x1f));
			break;
		case '4':
			db_printf("%%f%d", (insn & 0x1f));
			break;
		case 'e':
			db_printf("%%f%d", ((insn >> 25) & 0x1f));
			break;
		case 'i':
			/* simm13 -- signed */
			val = IF_SIMM(insn, 13);
			db_printf("%s0x%x", SIGN(val), (int)abs(val));
			break;
		case 'j':
			/* simm11 -- signed */
			val = IF_SIMM(insn, 11);
			db_printf("%s0x%x", SIGN(val), (int)abs(val));
			break;
		case 'l':
			val = (((insn>>20)&0x3)<<13)|(insn & 0x1fff);
			val = IF_SIMM(val, 16);
			db_printsym((db_addr_t)(loc + (4 * val)), DB_STGY_ANY);
			break;
		case 'm':
			db_printsym((db_addr_t)(loc + (4 * IF_SIMM(insn, 22))),
				DB_STGY_ANY);
			break;
		case 'u':
			db_printsym((db_addr_t)(loc + (4 * IF_SIMM(insn, 19))),
			    DB_STGY_ANY);
			break;
		case 'n':
			db_printsym((db_addr_t)(loc + (4 * IF_SIMM(insn, 30))),
			    DB_STGY_PROC);
			break;
		case 's':
			db_printf("%%asi");
			break;
		case 't':
			db_printf("0x%-2.2x", ((insn >> 5) & 0xff));
			break;
		case 'o':
			db_printf("%%fcc%d", ((insn >> 25) & 0x3));
			break;
		case 'p':
		case '7':
			db_printf("[%%%s + %%%s]",
				  regs[((insn >> 14) & 0x1f)],
				  regs[(insn & 0x1f)]);
			if (*f_ptr == '7')
				db_printf(" %d", ((insn >> 5) & 0xff));
			break;
		case 'q':
		case '8':
			val = IF_SIMM(insn, 13);
			db_printf("[%%%s %c 0x%x]",
				regs[((insn >> 14) & 0x1f)],
				(int)((val<0)?'-':'+'),
				(int)abs(val));
			if (*f_ptr == '8')
				db_printf(" %%asi");
			break;
		case '5':
			db_printf("%%fsr");
			break;
		case '6':
			db_printf("%%fsr");
			break;
		case '9':
			db_printf("0x%xl",
				  ((insn & 0xf) | ((insn >> 4) & 0x7)));
			break;
		case '0':
			db_printf("%%%s", ccodes[((insn >> 11) & 0x3) + 4]);
			break;
		case '.':
			db_printf("%%%s", ccodes[((insn >> 11) & 0x7)]);
			break;
		case 'r':
			db_printf("#%s", prefetch[((insn >> 25) & 0x1f)]);
			break;
		case 'A':
			db_printf("%%%s", priv_regs[((insn >> 14) & 0x1f)]);
			break;
		case 'B':
			db_printf("%%%s", state_regs[((insn >> 14) & 0x1f)]);
			break;
		case 'C':
			db_printf("%%hi(0x%x)", ((insn & 0x3fffff) << 10));
			break;
		case 'D':
			db_printf("0x%x", (insn & 0x1f));
			break;
		case 'E':
			db_printf("%d", (insn & 0x3f));
			break;
		case 'F':
			db_printf("%d", (insn & 0x3f));
			break;
		case 'G':
			db_printf("%%%s", priv_regs[((insn >> 25) & 0x1f)]);
			break;
		case 'H':
			db_printf("%%%s", state_regs[((insn >> 25) & 0x1f)]);
			break;
		default:
			db_printf("(UNKNOWN)");
			break;
		}
		if (*(++f_ptr))
			db_printf(", ");
	}

	db_printf("\n");

	return (loc + 4);
}