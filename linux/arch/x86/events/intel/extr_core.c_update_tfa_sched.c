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
struct cpu_hw_events {int /*<<< orphan*/  active_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  perf_pmu_resched (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_get_pmu () ; 

__attribute__((used)) static void update_tfa_sched(void *ignored)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * check if PMC3 is used
	 * and if so force schedule out for all event types all contexts
	 */
	if (test_bit(3, cpuc->active_mask))
		perf_pmu_resched(x86_get_pmu());
}