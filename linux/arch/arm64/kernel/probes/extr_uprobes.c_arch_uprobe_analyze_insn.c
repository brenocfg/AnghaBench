#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
struct mm_struct {TYPE_1__ context; } ;
struct arch_uprobe {int simulate; int /*<<< orphan*/  api; int /*<<< orphan*/ * insn; } ;
typedef  int /*<<< orphan*/  probe_opcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_INSN_SIZE ; 
 int EINVAL ; 
 int ENOTSUPP ; 
#define  INSN_GOOD_NO_SLOT 129 
#define  INSN_REJECTED 128 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 int MMCF_AARCH32 ; 
 int arm_probe_decode_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int arch_uprobe_analyze_insn(struct arch_uprobe *auprobe, struct mm_struct *mm,
		unsigned long addr)
{
	probe_opcode_t insn;

	/* TODO: Currently we do not support AARCH32 instruction probing */
	if (mm->context.flags & MMCF_AARCH32)
		return -ENOTSUPP;
	else if (!IS_ALIGNED(addr, AARCH64_INSN_SIZE))
		return -EINVAL;

	insn = *(probe_opcode_t *)(&auprobe->insn[0]);

	switch (arm_probe_decode_insn(insn, &auprobe->api)) {
	case INSN_REJECTED:
		return -EINVAL;

	case INSN_GOOD_NO_SLOT:
		auprobe->simulate = true;
		break;

	default:
		break;
	}

	return 0;
}