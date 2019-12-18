#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rs; scalar_t__ func; } ;
struct TYPE_7__ {scalar_t__ rt; } ;
struct TYPE_5__ {scalar_t__ op; } ;
struct TYPE_8__ {int word; TYPE_2__ RType; TYPE_3__ IType; TYPE_1__ JType; } ;
typedef  TYPE_4__ InstFmt ;

/* Variables and functions */
 int IT_BRANCH ; 
 int IT_CALL ; 
 int IT_LOAD ; 
 int IT_STORE ; 
#define  OP_BCOND 166 
#define  OP_BCx 165 
#define  OP_BCy 164 
#define  OP_BEQ 163 
#define  OP_BEQL 162 
#define  OP_BGEZ 161 
#define  OP_BGEZAL 160 
#define  OP_BGEZALL 159 
#define  OP_BGEZL 158 
#define  OP_BGTZ 157 
#define  OP_BGTZL 156 
#define  OP_BLEZ 155 
#define  OP_BLEZL 154 
#define  OP_BLTZ 153 
#define  OP_BLTZAL 152 
#define  OP_BLTZALL 151 
#define  OP_BLTZL 150 
#define  OP_BNE 149 
#define  OP_BNEL 148 
#define  OP_COP1 147 
#define  OP_J 146 
#define  OP_JAL 145 
#define  OP_JALR 144 
#define  OP_JR 143 
#define  OP_LB 142 
#define  OP_LBU 141 
#define  OP_LD 140 
#define  OP_LH 139 
#define  OP_LHU 138 
#define  OP_LW 137 
#define  OP_LWC1 136 
#define  OP_LWU 135 
#define  OP_SB 134 
#define  OP_SD 133 
#define  OP_SH 132 
#define  OP_SPECIAL 131 
#define  OP_SW 130 
#define  OP_SWC1 129 
#define  OP_SYSCALL 128 

int
db_inst_type(int ins)
{
	InstFmt inst;
	int	ityp = 0;

	inst.word = ins;
	switch ((int)inst.JType.op) {
	case OP_SPECIAL:
		switch ((int)inst.RType.func) {
		case OP_JR:
			ityp = IT_BRANCH;
			break;
		case OP_JALR:
		case OP_SYSCALL:
			ityp = IT_CALL;
			break;
		}
		break;

	case OP_BCOND:
		switch ((int)inst.IType.rt) {
		case OP_BLTZ:
		case OP_BLTZL:
		case OP_BGEZ:
		case OP_BGEZL:
			ityp = IT_BRANCH;
			break;

		case OP_BLTZAL:
		case OP_BLTZALL:
		case OP_BGEZAL:
		case OP_BGEZALL:
			ityp = IT_CALL;
			break;
		}
		break;

	case OP_JAL:
		ityp = IT_CALL;
		break;

	case OP_J:
	case OP_BEQ:
	case OP_BEQL:
	case OP_BNE:
	case OP_BNEL:
	case OP_BLEZ:
	case OP_BLEZL:
	case OP_BGTZ:
	case OP_BGTZL:
		ityp = IT_BRANCH;
		break;

	case OP_COP1:
		switch (inst.RType.rs) {
		case OP_BCx:
		case OP_BCy:
			ityp = IT_BRANCH;
			break;
		}
		break;

	case OP_LB:
	case OP_LH:
	case OP_LW:
	case OP_LD:
	case OP_LBU:
	case OP_LHU:
	case OP_LWU:
	case OP_LWC1:
		ityp = IT_LOAD;
		break;

	case OP_SB:
	case OP_SH:
	case OP_SW:
	case OP_SD:  
	case OP_SWC1:
		ityp = IT_STORE;
		break;
	}
	return (ityp);
}