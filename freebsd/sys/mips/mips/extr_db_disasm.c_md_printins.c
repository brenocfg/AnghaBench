#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t rt; size_t rs; size_t op; scalar_t__ imm; } ;
struct TYPE_7__ {int op; int target; } ;
struct TYPE_6__ {size_t func; size_t fmt; int /*<<< orphan*/  ft; int /*<<< orphan*/  fs; int /*<<< orphan*/  fd; } ;
struct TYPE_8__ {size_t func; size_t rt; size_t rd; size_t rs; int /*<<< orphan*/  shamt; } ;
struct TYPE_10__ {int word; TYPE_4__ IType; TYPE_2__ JType; TYPE_1__ FRType; TYPE_3__ RType; } ;
typedef  TYPE_5__ InstFmt ;

/* Variables and functions */
 size_t COPz_BC_TF_MASK ; 
#define  OP_ADDI 202 
#define  OP_ADDIU 201 
 size_t OP_ADDU ; 
#define  OP_ANDI 200 
#define  OP_BCOND 199 
#define  OP_BCx 198 
#define  OP_BCy 197 
#define  OP_BEQ 196 
#define  OP_BEQL 195 
#define  OP_BGTZ 194 
#define  OP_BGTZL 193 
#define  OP_BLEZ 192 
#define  OP_BLEZL 191 
#define  OP_BNE 190 
#define  OP_BNEL 189 
#define  OP_BREAK 188 
#define  OP_CF 187 
#define  OP_COP0 186 
#define  OP_COP1 185 
#define  OP_CT 184 
#define  OP_DADDI 183 
#define  OP_DADDIU 182 
#define  OP_DDIV 181 
#define  OP_DDIVU 180 
#define  OP_DIV 179 
#define  OP_DIVU 178 
#define  OP_DMF 177 
#define  OP_DMT 176 
#define  OP_DMULT 175 
#define  OP_DMULTU 174 
#define  OP_DSLL 173 
#define  OP_DSLL32 172 
#define  OP_DSLLV 171 
#define  OP_DSRA 170 
#define  OP_DSRA32 169 
#define  OP_DSRAV 168 
#define  OP_DSRL 167 
#define  OP_DSRL32 166 
#define  OP_DSRLV 165 
#define  OP_J 164 
#define  OP_JAL 163 
#define  OP_JALR 162 
#define  OP_JR 161 
#define  OP_LB 160 
#define  OP_LBU 159 
#define  OP_LD 158 
#define  OP_LH 157 
#define  OP_LHU 156 
#define  OP_LUI 155 
#define  OP_LW 154 
#define  OP_LWC1 153 
#define  OP_LWU 152 
#define  OP_MF 151 
#define  OP_MFHI 150 
#define  OP_MFLO 149 
#define  OP_MT 148 
#define  OP_MTHI 147 
#define  OP_MTLO 146 
#define  OP_MULT 145 
#define  OP_MULTU 144 
#define  OP_ORI 143 
#define  OP_SB 142 
#define  OP_SD 141 
#define  OP_SH 140 
#define  OP_SLL 139 
#define  OP_SLLV 138 
#define  OP_SPECIAL 137 
#define  OP_SRA 136 
#define  OP_SRAV 135 
#define  OP_SRL 134 
#define  OP_SRLV 133 
#define  OP_SW 132 
#define  OP_SWC1 131 
#define  OP_SYNC 130 
#define  OP_SYSCALL 129 
#define  OP_XORI 128 
 int /*<<< orphan*/ * bcond_name ; 
 int /*<<< orphan*/ * c0_opname ; 
 int /*<<< orphan*/ * c0_reg ; 
 int /*<<< orphan*/ * cop1_name ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/ * fmt_name ; 
 int /*<<< orphan*/ * op_name ; 
 int /*<<< orphan*/ * reg_name ; 
 int /*<<< orphan*/ * spec_name ; 

__attribute__((used)) static int
md_printins(int ins, int mdbdot)
{
	InstFmt i;
	int delay = 0;

	i.word = ins;

	switch (i.JType.op) {
	case OP_SPECIAL:
		if (i.word == 0) {
			db_printf("nop");
			break;
		}
		if (i.RType.func == OP_ADDU && i.RType.rt == 0) {
			db_printf("move\t%s,%s",
			    reg_name[i.RType.rd], reg_name[i.RType.rs]);
			break;
		}
		db_printf("%s", spec_name[i.RType.func]);
		switch (i.RType.func) {
		case OP_SLL:
		case OP_SRL:
		case OP_SRA:
		case OP_DSLL:
		case OP_DSRL:
		case OP_DSRA:
		case OP_DSLL32:
		case OP_DSRL32:
		case OP_DSRA32:
			db_printf("\t%s,%s,%d", reg_name[i.RType.rd],
			    reg_name[i.RType.rt], i.RType.shamt);
			break;

		case OP_SLLV:
		case OP_SRLV:
		case OP_SRAV:
		case OP_DSLLV:
		case OP_DSRLV:
		case OP_DSRAV:
			db_printf("\t%s,%s,%s", reg_name[i.RType.rd],
			    reg_name[i.RType.rt], reg_name[i.RType.rs]);
			break;

		case OP_MFHI:
		case OP_MFLO:
			db_printf("\t%s", reg_name[i.RType.rd]);
			break;

		case OP_JR:
		case OP_JALR:
			delay = 1;
			/* FALLTHROUGH */
		case OP_MTLO:
		case OP_MTHI:
			db_printf("\t%s", reg_name[i.RType.rs]);
			break;

		case OP_MULT:
		case OP_MULTU:
		case OP_DMULT:
		case OP_DMULTU:
		case OP_DIV:
		case OP_DIVU:
		case OP_DDIV:
		case OP_DDIVU:
			db_printf("\t%s,%s",
			    reg_name[i.RType.rs], reg_name[i.RType.rt]);
			break;

		case OP_SYSCALL:
		case OP_SYNC:
			break;

		case OP_BREAK:
			db_printf("\t%d", (i.RType.rs << 5) | i.RType.rt);
			break;

		default:
			db_printf("\t%s,%s,%s", reg_name[i.RType.rd],
			    reg_name[i.RType.rs], reg_name[i.RType.rt]);
		}
		break;

	case OP_BCOND:
		db_printf("%s\t%s,", bcond_name[i.IType.rt],
		    reg_name[i.IType.rs]);
		goto pr_displ;

	case OP_BLEZ:
	case OP_BLEZL:
	case OP_BGTZ:
	case OP_BGTZL:
		db_printf("%s\t%s,", op_name[i.IType.op],
		    reg_name[i.IType.rs]);
		goto pr_displ;

	case OP_BEQ:
	case OP_BEQL:
		if (i.IType.rs == 0 && i.IType.rt == 0) {
			db_printf("b\t");
			goto pr_displ;
		}
		/* FALLTHROUGH */
	case OP_BNE:
	case OP_BNEL:
		db_printf("%s\t%s,%s,", op_name[i.IType.op],
		    reg_name[i.IType.rs], reg_name[i.IType.rt]);
	pr_displ:
		delay = 1;
		db_printf("0x%08x", mdbdot + 4 + ((short)i.IType.imm << 2));
		break;

	case OP_COP0:
		switch (i.RType.rs) {
		case OP_BCx:
		case OP_BCy:
			db_printf("bc0%c\t",
			    "ft"[i.RType.rt & COPz_BC_TF_MASK]);
			goto pr_displ;

		case OP_MT:
			db_printf("mtc0\t%s,%s",
			    reg_name[i.RType.rt], c0_reg[i.RType.rd]);
			break;

		case OP_DMT:
			db_printf("dmtc0\t%s,%s",
			    reg_name[i.RType.rt], c0_reg[i.RType.rd]);
			break;

		case OP_MF:
			db_printf("mfc0\t%s,%s",
			    reg_name[i.RType.rt], c0_reg[i.RType.rd]);
			break;

		case OP_DMF:
			db_printf("dmfc0\t%s,%s",
			    reg_name[i.RType.rt], c0_reg[i.RType.rd]);
			break;

		default:
			db_printf("%s", c0_opname[i.FRType.func]);
		}
		break;

	case OP_COP1:
		switch (i.RType.rs) {
		case OP_BCx:
		case OP_BCy:
			db_printf("bc1%c\t",
			    "ft"[i.RType.rt & COPz_BC_TF_MASK]);
			goto pr_displ;

		case OP_MT:
			db_printf("mtc1\t%s,f%d",
			    reg_name[i.RType.rt], i.RType.rd);
			break;

		case OP_MF:
			db_printf("mfc1\t%s,f%d",
			    reg_name[i.RType.rt], i.RType.rd);
			break;

		case OP_CT:
			db_printf("ctc1\t%s,f%d",
			    reg_name[i.RType.rt], i.RType.rd);
			break;

		case OP_CF:
			db_printf("cfc1\t%s,f%d",
			    reg_name[i.RType.rt], i.RType.rd);
			break;

		default:
			db_printf("%s.%s\tf%d,f%d,f%d",
			    cop1_name[i.FRType.func], fmt_name[i.FRType.fmt],
			    i.FRType.fd, i.FRType.fs, i.FRType.ft);
		}
		break;

	case OP_J:
	case OP_JAL:
		db_printf("%s\t", op_name[i.JType.op]);
		db_printf("0x%8x",(mdbdot & 0xF0000000) | (i.JType.target << 2));
		delay = 1;
		break;

	case OP_LWC1:
	case OP_SWC1:
		db_printf("%s\tf%d,", op_name[i.IType.op], i.IType.rt);
		goto loadstore;

	case OP_LB:
	case OP_LH:
	case OP_LW:
	case OP_LD:
	case OP_LBU:
	case OP_LHU:
	case OP_LWU:
	case OP_SB:
	case OP_SH:
	case OP_SW:
	case OP_SD:
		db_printf("%s\t%s,", op_name[i.IType.op],
		    reg_name[i.IType.rt]);
	loadstore:
		db_printf("%d(%s)", (short)i.IType.imm, reg_name[i.IType.rs]);
		break;

	case OP_ORI:
	case OP_XORI:
		if (i.IType.rs == 0) {
			db_printf("li\t%s,0x%x",
			    reg_name[i.IType.rt], i.IType.imm);
			break;
		}
		/* FALLTHROUGH */
	case OP_ANDI:
		db_printf("%s\t%s,%s,0x%x", op_name[i.IType.op],
		    reg_name[i.IType.rt], reg_name[i.IType.rs], i.IType.imm);
		break;

	case OP_LUI:
		db_printf("%s\t%s,0x%x", op_name[i.IType.op],
		    reg_name[i.IType.rt], i.IType.imm);
		break;

	case OP_ADDI:
	case OP_DADDI:
	case OP_ADDIU:
	case OP_DADDIU:
		if (i.IType.rs == 0) {
			db_printf("li\t%s,%d", reg_name[i.IType.rt],
			    (short)i.IType.imm);
			break;
		}
		/* FALLTHROUGH */
	default:
		db_printf("%s\t%s,%s,%d", op_name[i.IType.op],
		    reg_name[i.IType.rt], reg_name[i.IType.rs],
		    (short)i.IType.imm);
	}
	db_printf("\n");
	return (delay);
}