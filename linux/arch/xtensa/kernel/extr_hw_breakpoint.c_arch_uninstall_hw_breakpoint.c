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
struct perf_event {int dummy; } ;
struct arch_hw_breakpoint {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SREG_DBREAKC ; 
 int /*<<< orphan*/  SREG_IBREAKENABLE ; 
 int /*<<< orphan*/  XCHAL_NUM_DBREAK ; 
 int /*<<< orphan*/  XCHAL_NUM_IBREAK ; 
 scalar_t__ XTENSA_BREAKPOINT_EXECUTE ; 
 int /*<<< orphan*/  bp_on_reg ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 int free_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_on_reg ; 
 unsigned long xtensa_get_sr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtensa_set_sr (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtensa_wsr (int /*<<< orphan*/ ,scalar_t__) ; 

void arch_uninstall_hw_breakpoint(struct perf_event *bp)
{
	struct arch_hw_breakpoint *info = counter_arch_bp(bp);
	int i;

	if (info->type == XTENSA_BREAKPOINT_EXECUTE) {
		unsigned long ibreakenable;

		/* Breakpoint */
		i = free_slot(this_cpu_ptr(bp_on_reg), XCHAL_NUM_IBREAK, bp);
		if (i >= 0) {
			ibreakenable = xtensa_get_sr(SREG_IBREAKENABLE);
			xtensa_set_sr(ibreakenable & ~(1 << i),
				      SREG_IBREAKENABLE);
		}
	} else {
		/* Watchpoint */
		i = free_slot(this_cpu_ptr(wp_on_reg), XCHAL_NUM_DBREAK, bp);
		if (i >= 0)
			xtensa_wsr(0, SREG_DBREAKC + i);
	}
}