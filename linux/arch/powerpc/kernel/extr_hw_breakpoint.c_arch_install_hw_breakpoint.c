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
struct arch_hw_breakpoint {int dummy; } ;
struct TYPE_3__ {struct perf_event* last_hit_ubp; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_breakpoint (struct arch_hw_breakpoint*) ; 
 int /*<<< orphan*/  bp_per_reg ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 TYPE_2__* current ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ *) ; 

int arch_install_hw_breakpoint(struct perf_event *bp)
{
	struct arch_hw_breakpoint *info = counter_arch_bp(bp);
	struct perf_event **slot = this_cpu_ptr(&bp_per_reg);

	*slot = bp;

	/*
	 * Do not install DABR values if the instruction must be single-stepped.
	 * If so, DABR will be populated in single_step_dabr_instruction().
	 */
	if (current->thread.last_hit_ubp != bp)
		__set_breakpoint(info);

	return 0;
}