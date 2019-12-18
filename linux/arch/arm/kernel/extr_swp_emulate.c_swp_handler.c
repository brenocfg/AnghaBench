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
struct pt_regs {int ARM_pc; unsigned int* uregs; int /*<<< orphan*/  ARM_cpsr; } ;
struct TYPE_2__ {scalar_t__ pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
#define  ARM_OPCODE_CONDTEST_FAIL 130 
#define  ARM_OPCODE_CONDTEST_PASS 129 
#define  ARM_OPCODE_CONDTEST_UNCOND 128 
 int EFAULT ; 
 int EINVAL ; 
 size_t EXTRACT_REG_NUM (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_COUNT_SW_EMULATION_FAULTS ; 
 int /*<<< orphan*/  RN_OFFSET ; 
 int /*<<< orphan*/  RT2_OFFSET ; 
 int /*<<< orphan*/  RT_OFFSET ; 
 unsigned int TYPE_SWPB ; 
 int /*<<< orphan*/  access_ok (unsigned int,int) ; 
 unsigned int arm_check_condition (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 unsigned int emulate_swpX (unsigned int,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,...) ; 
 scalar_t__ previous_pid ; 
 int /*<<< orphan*/  set_segfault (struct pt_regs*,unsigned int) ; 

__attribute__((used)) static int swp_handler(struct pt_regs *regs, unsigned int instr)
{
	unsigned int address, destreg, data, type;
	unsigned int res = 0;

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, regs->ARM_pc);

	res = arm_check_condition(instr, regs->ARM_cpsr);
	switch (res) {
	case ARM_OPCODE_CONDTEST_PASS:
		break;
	case ARM_OPCODE_CONDTEST_FAIL:
		/* Condition failed - return to next instruction */
		regs->ARM_pc += 4;
		return 0;
	case ARM_OPCODE_CONDTEST_UNCOND:
		/* If unconditional encoding - not a SWP, undef */
		return -EFAULT;
	default:
		return -EINVAL;
	}

	if (current->pid != previous_pid) {
		pr_debug("\"%s\" (%ld) uses deprecated SWP{B} instruction\n",
			 current->comm, (unsigned long)current->pid);
		previous_pid = current->pid;
	}

	address = regs->uregs[EXTRACT_REG_NUM(instr, RN_OFFSET)];
	data	= regs->uregs[EXTRACT_REG_NUM(instr, RT2_OFFSET)];
	destreg = EXTRACT_REG_NUM(instr, RT_OFFSET);

	type = instr & TYPE_SWPB;

	pr_debug("addr in r%d->0x%08x, dest is r%d, source in r%d->0x%08x)\n",
		 EXTRACT_REG_NUM(instr, RN_OFFSET), address,
		 destreg, EXTRACT_REG_NUM(instr, RT2_OFFSET), data);

	/* Check access in reasonable access range for both SWP and SWPB */
	if (!access_ok((address & ~3), 4)) {
		pr_debug("SWP{B} emulation: access to %p not allowed!\n",
			 (void *)address);
		res = -EFAULT;
	} else {
		res = emulate_swpX(address, &data, type);
	}

	if (res == 0) {
		/*
		 * On successful emulation, revert the adjustment to the PC
		 * made in kernel/traps.c in order to resume execution at the
		 * instruction following the SWP{B}.
		 */
		regs->ARM_pc += 4;
		regs->uregs[destreg] = data;
	} else if (res == -EFAULT) {
		/*
		 * Memory errors do not mean emulation failed.
		 * Set up signal info to return SEGV, then return OK
		 */
		set_segfault(regs, address);
	}

	return 0;
}