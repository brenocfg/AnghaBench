#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct pt_insn_ext {void* iclass; int /*<<< orphan*/  variant; } ;
struct pt_insn {void* iclass; } ;
struct TYPE_3__ {int /*<<< orphan*/  osz; int /*<<< orphan*/  f3; int /*<<< orphan*/  rex_r; scalar_t__ vex; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct pt_ild {scalar_t__ nominal_opcode; scalar_t__ map; TYPE_2__ u; int /*<<< orphan*/  modrm_byte; } ;

/* Variables and functions */
 void* PTI_INST_CALL_9A ; 
 void* PTI_INST_CALL_E8 ; 
 void* PTI_INST_CALL_FFr2 ; 
 void* PTI_INST_CALL_FFr3 ; 
 void* PTI_INST_INT ; 
 void* PTI_INST_INT1 ; 
 void* PTI_INST_INT3 ; 
 void* PTI_INST_INTO ; 
 void* PTI_INST_INVALID ; 
 void* PTI_INST_IRET ; 
 void* PTI_INST_JCC ; 
 void* PTI_INST_JMP_E9 ; 
 void* PTI_INST_JMP_EA ; 
 void* PTI_INST_JMP_EB ; 
 void* PTI_INST_JMP_FFr4 ; 
 void* PTI_INST_JMP_FFr5 ; 
 void* PTI_INST_JrCXZ ; 
 void* PTI_INST_LOOP ; 
 void* PTI_INST_LOOPE ; 
 void* PTI_INST_LOOPNE ; 
 void* PTI_INST_MOV_CR3 ; 
 void* PTI_INST_PTWRITE ; 
 void* PTI_INST_RET_C2 ; 
 void* PTI_INST_RET_C3 ; 
 void* PTI_INST_RET_CA ; 
 void* PTI_INST_RET_CB ; 
 void* PTI_INST_SYSCALL ; 
 void* PTI_INST_SYSENTER ; 
 void* PTI_INST_SYSEXIT ; 
 void* PTI_INST_SYSRET ; 
 void* PTI_INST_VMCALL ; 
 void* PTI_INST_VMLAUNCH ; 
 void* PTI_INST_VMPTRLD ; 
 void* PTI_INST_VMRESUME ; 
 scalar_t__ PTI_MAP_0 ; 
 scalar_t__ PTI_MAP_1 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pte_internal ; 
 int pti_get_modrm_mod (struct pt_ild const*) ; 
 int pti_get_modrm_reg (struct pt_ild const*) ; 
 void* ptic_call ; 
 void* ptic_cond_jump ; 
 void* ptic_far_call ; 
 void* ptic_far_jump ; 
 void* ptic_far_return ; 
 void* ptic_jump ; 
 void* ptic_other ; 
 void* ptic_ptwrite ; 
 void* ptic_return ; 
 int set_branch_target (struct pt_insn_ext*,struct pt_ild const*) ; 

__attribute__((used)) static int pt_instruction_decode(struct pt_insn *insn, struct pt_insn_ext *iext,
				 const struct pt_ild *ild)
{
	uint8_t opcode, map;

	if (!iext || !ild)
		return -pte_internal;

	iext->iclass = PTI_INST_INVALID;
	memset(&iext->variant, 0, sizeof(iext->variant));

	insn->iclass = ptic_other;

	opcode = ild->nominal_opcode;
	map = ild->map;

	if (map > PTI_MAP_1)
		return 0;	/* uninteresting */
	if (ild->u.s.vex)
		return 0;	/* uninteresting */

	/* PTI_INST_JCC,   70...7F, 0F (0x80...0x8F) */
	if (opcode >= 0x70 && opcode <= 0x7F) {
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_cond_jump;
			iext->iclass = PTI_INST_JCC;

			return set_branch_target(iext, ild);
		}
		return 0;
	}
	if (opcode >= 0x80 && opcode <= 0x8F) {
		if (map == PTI_MAP_1) {
			insn->iclass = ptic_cond_jump;
			iext->iclass = PTI_INST_JCC;

			return set_branch_target(iext, ild);
		}
		return 0;
	}

	switch (ild->nominal_opcode) {
	case 0x9A:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_far_call;
			iext->iclass = PTI_INST_CALL_9A;
		}
		return 0;

	case 0xFF:
		if (map == PTI_MAP_0) {
			uint8_t reg = pti_get_modrm_reg(ild);

			if (reg == 2) {
				insn->iclass = ptic_call;
				iext->iclass = PTI_INST_CALL_FFr2;
			} else if (reg == 3) {
				insn->iclass = ptic_far_call;
				iext->iclass = PTI_INST_CALL_FFr3;
			} else if (reg == 4) {
				insn->iclass = ptic_jump;
				iext->iclass = PTI_INST_JMP_FFr4;
			} else if (reg == 5) {
				insn->iclass = ptic_far_jump;
				iext->iclass = PTI_INST_JMP_FFr5;
			}
		}
		return 0;

	case 0xE8:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_call;
			iext->iclass = PTI_INST_CALL_E8;

			return set_branch_target(iext, ild);
		}
		return 0;

	case 0xCD:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_far_call;
			iext->iclass = PTI_INST_INT;
		}

		return 0;

	case 0xCC:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_far_call;
			iext->iclass = PTI_INST_INT3;
		}

		return 0;

	case 0xCE:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_far_call;
			iext->iclass = PTI_INST_INTO;
		}

		return 0;

	case 0xF1:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_far_call;
			iext->iclass = PTI_INST_INT1;
		}

		return 0;

	case 0xCF:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_far_return;
			iext->iclass = PTI_INST_IRET;
		}
		return 0;

	case 0xE9:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_jump;
			iext->iclass = PTI_INST_JMP_E9;

			return set_branch_target(iext, ild);
		}
		return 0;

	case 0xEA:
		if (map == PTI_MAP_0) {
			/* Far jumps are treated as indirect jumps. */
			insn->iclass = ptic_far_jump;
			iext->iclass = PTI_INST_JMP_EA;
		}
		return 0;

	case 0xEB:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_jump;
			iext->iclass = PTI_INST_JMP_EB;

			return set_branch_target(iext, ild);
		}
		return 0;

	case 0xE3:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_cond_jump;
			iext->iclass = PTI_INST_JrCXZ;

			return set_branch_target(iext, ild);
		}
		return 0;

	case 0xE0:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_cond_jump;
			iext->iclass = PTI_INST_LOOPNE;

			return set_branch_target(iext, ild);
		}
		return 0;

	case 0xE1:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_cond_jump;
			iext->iclass = PTI_INST_LOOPE;

			return set_branch_target(iext, ild);
		}
		return 0;

	case 0xE2:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_cond_jump;
			iext->iclass = PTI_INST_LOOP;

			return set_branch_target(iext, ild);
		}
		return 0;

	case 0x22:
		if (map == PTI_MAP_1)
			if (pti_get_modrm_reg(ild) == 3)
				if (!ild->u.s.rex_r)
					iext->iclass = PTI_INST_MOV_CR3;

		return 0;

	case 0xC3:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_return;
			iext->iclass = PTI_INST_RET_C3;
		}
		return 0;

	case 0xC2:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_return;
			iext->iclass = PTI_INST_RET_C2;
		}
		return 0;

	case 0xCB:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_far_return;
			iext->iclass = PTI_INST_RET_CB;
		}
		return 0;

	case 0xCA:
		if (map == PTI_MAP_0) {
			insn->iclass = ptic_far_return;
			iext->iclass = PTI_INST_RET_CA;
		}
		return 0;

	case 0x05:
		if (map == PTI_MAP_1) {
			insn->iclass = ptic_far_call;
			iext->iclass = PTI_INST_SYSCALL;
		}
		return 0;

	case 0x34:
		if (map == PTI_MAP_1) {
			insn->iclass = ptic_far_call;
			iext->iclass = PTI_INST_SYSENTER;
		}
		return 0;

	case 0x35:
		if (map == PTI_MAP_1) {
			insn->iclass = ptic_far_return;
			iext->iclass = PTI_INST_SYSEXIT;
		}
		return 0;

	case 0x07:
		if (map == PTI_MAP_1) {
			insn->iclass = ptic_far_return;
			iext->iclass = PTI_INST_SYSRET;
		}
		return 0;

	case 0x01:
		if (map == PTI_MAP_1) {
			switch (ild->modrm_byte) {
			case 0xc1:
				insn->iclass = ptic_far_call;
				iext->iclass = PTI_INST_VMCALL;
				break;

			case 0xc2:
				insn->iclass = ptic_far_return;
				iext->iclass = PTI_INST_VMLAUNCH;
				break;

			case 0xc3:
				insn->iclass = ptic_far_return;
				iext->iclass = PTI_INST_VMRESUME;
				break;

			default:
				break;
			}
		}
		return 0;

	case 0xc7:
		if (map == PTI_MAP_1 &&
		    pti_get_modrm_mod(ild) != 3 &&
		    pti_get_modrm_reg(ild) == 6)
			iext->iclass = PTI_INST_VMPTRLD;

		return 0;

	case 0xae:
		if (map == PTI_MAP_1 && ild->u.s.f3 && !ild->u.s.osz &&
		    pti_get_modrm_reg(ild) == 4) {
			insn->iclass = ptic_ptwrite;
			iext->iclass = PTI_INST_PTWRITE;
		}
		return 0;

	default:
		return 0;
	}
}