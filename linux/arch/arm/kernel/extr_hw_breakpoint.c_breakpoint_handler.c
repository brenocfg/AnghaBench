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
typedef  int u32 ;
struct pt_regs {int ARM_pc; } ;
struct perf_event {int /*<<< orphan*/  overflow_handler; } ;
struct arch_hw_breakpoint_ctrl {int len; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;
struct arch_hw_breakpoint {int trigger; TYPE_1__ step_ctrl; } ;

/* Variables and functions */
 scalar_t__ ARM_BASE_BCR ; 
 scalar_t__ ARM_BASE_BVR ; 
 int /*<<< orphan*/  bp_on_reg ; 
 int core_num_brps ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 int /*<<< orphan*/  decode_ctrl_reg (int,struct arch_hw_breakpoint_ctrl*) ; 
 int /*<<< orphan*/  disable_single_step (struct perf_event*) ; 
 int /*<<< orphan*/  enable_single_step (struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_bp_event (struct perf_event*,struct pt_regs*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int read_wb_reg (scalar_t__) ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchpoint_single_step_handler (int) ; 

__attribute__((used)) static void breakpoint_handler(unsigned long unknown, struct pt_regs *regs)
{
	int i;
	u32 ctrl_reg, val, addr;
	struct perf_event *bp, **slots;
	struct arch_hw_breakpoint *info;
	struct arch_hw_breakpoint_ctrl ctrl;

	slots = this_cpu_ptr(bp_on_reg);

	/* The exception entry code places the amended lr in the PC. */
	addr = regs->ARM_pc;

	/* Check the currently installed breakpoints first. */
	for (i = 0; i < core_num_brps; ++i) {
		rcu_read_lock();

		bp = slots[i];

		if (bp == NULL)
			goto unlock;

		info = counter_arch_bp(bp);

		/* Check if the breakpoint value matches. */
		val = read_wb_reg(ARM_BASE_BVR + i);
		if (val != (addr & ~0x3))
			goto mismatch;

		/* Possible match, check the byte address select to confirm. */
		ctrl_reg = read_wb_reg(ARM_BASE_BCR + i);
		decode_ctrl_reg(ctrl_reg, &ctrl);
		if ((1 << (addr & 0x3)) & ctrl.len) {
			info->trigger = addr;
			pr_debug("breakpoint fired: address = 0x%x\n", addr);
			perf_bp_event(bp, regs);
			if (!bp->overflow_handler)
				enable_single_step(bp, addr);
			goto unlock;
		}

mismatch:
		/* If we're stepping a breakpoint, it can now be restored. */
		if (info->step_ctrl.enabled)
			disable_single_step(bp);
unlock:
		rcu_read_unlock();
	}

	/* Handle any pending watchpoint single-step breakpoints. */
	watchpoint_single_step_handler(addr);
}