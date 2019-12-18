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
struct pt_regs {unsigned long nip; int trap; int /*<<< orphan*/  msr; } ;
struct TYPE_2__ {int /*<<< orphan*/ * insn; } ;
struct kprobe {TYPE_1__ ainsn; int /*<<< orphan*/ * addr; } ;
struct instruction_op {int dummy; } ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_KERNEL ; 
 int analyse_instr (struct instruction_op*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emulate_update_regs (struct pt_regs*,struct instruction_op*) ; 
 int /*<<< orphan*/  is_conditional_branch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_kernel_addr (unsigned long) ; 
 int /*<<< orphan*/  kretprobe_trampoline ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long can_optimize(struct kprobe *p)
{
	struct pt_regs regs;
	struct instruction_op op;
	unsigned long nip = 0;

	/*
	 * kprobe placed for kretprobe during boot time
	 * has a 'nop' instruction, which can be emulated.
	 * So further checks can be skipped.
	 */
	if (p->addr == (kprobe_opcode_t *)&kretprobe_trampoline)
		return (unsigned long)p->addr + sizeof(kprobe_opcode_t);

	/*
	 * We only support optimizing kernel addresses, but not
	 * module addresses.
	 *
	 * FIXME: Optimize kprobes placed in module addresses.
	 */
	if (!is_kernel_addr((unsigned long)p->addr))
		return 0;

	memset(&regs, 0, sizeof(struct pt_regs));
	regs.nip = (unsigned long)p->addr;
	regs.trap = 0x0;
	regs.msr = MSR_KERNEL;

	/*
	 * Kprobe placed in conditional branch instructions are
	 * not optimized, as we can't predict the nip prior with
	 * dummy pt_regs and can not ensure that the return branch
	 * from detour buffer falls in the range of address (i.e 32MB).
	 * A branch back from trampoline is set up in the detour buffer
	 * to the nip returned by the analyse_instr() here.
	 *
	 * Ensure that the instruction is not a conditional branch,
	 * and that can be emulated.
	 */
	if (!is_conditional_branch(*p->ainsn.insn) &&
			analyse_instr(&op, &regs, *p->ainsn.insn) == 1) {
		emulate_update_regs(&regs, &op);
		nip = regs.nip;
	}

	return nip;
}