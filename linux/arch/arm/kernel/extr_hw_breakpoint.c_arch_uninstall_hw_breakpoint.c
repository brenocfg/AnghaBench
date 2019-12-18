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
struct perf_event {int dummy; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct arch_hw_breakpoint {TYPE_2__ step_ctrl; TYPE_1__ ctrl; } ;

/* Variables and functions */
 int ARM_BASE_BCR ; 
 int ARM_BASE_WCR ; 
 scalar_t__ ARM_BREAKPOINT_EXECUTE ; 
 int /*<<< orphan*/  bp_on_reg ; 
 int core_num_brps ; 
 int core_num_wrps ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_on_reg ; 
 int /*<<< orphan*/  write_wb_reg (int,int /*<<< orphan*/ ) ; 

void arch_uninstall_hw_breakpoint(struct perf_event *bp)
{
	struct arch_hw_breakpoint *info = counter_arch_bp(bp);
	struct perf_event **slot, **slots;
	int i, max_slots, base;

	if (info->ctrl.type == ARM_BREAKPOINT_EXECUTE) {
		/* Breakpoint */
		base = ARM_BASE_BCR;
		slots = this_cpu_ptr(bp_on_reg);
		max_slots = core_num_brps;
	} else {
		/* Watchpoint */
		base = ARM_BASE_WCR;
		slots = this_cpu_ptr(wp_on_reg);
		max_slots = core_num_wrps;
	}

	/* Remove the breakpoint. */
	for (i = 0; i < max_slots; ++i) {
		slot = &slots[i];

		if (*slot == bp) {
			*slot = NULL;
			break;
		}
	}

	if (i == max_slots) {
		pr_warn("Can't find any breakpoint slot\n");
		return;
	}

	/* Ensure that we disable the mismatch breakpoint. */
	if (info->ctrl.type != ARM_BREAKPOINT_EXECUTE &&
	    info->step_ctrl.enabled) {
		i = 0;
		base = ARM_BASE_BCR + core_num_brps;
	}

	/* Reset the control register. */
	write_wb_reg(base + i, 0);
}