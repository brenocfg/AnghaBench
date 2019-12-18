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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  bp_per_reg ; 
 int /*<<< orphan*/  hw_breakpoint_disable () ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ *) ; 

void arch_uninstall_hw_breakpoint(struct perf_event *bp)
{
	struct perf_event **slot = this_cpu_ptr(&bp_per_reg);

	if (*slot != bp) {
		WARN_ONCE(1, "Can't find the breakpoint");
		return;
	}

	*slot = NULL;
	hw_breakpoint_disable();
}