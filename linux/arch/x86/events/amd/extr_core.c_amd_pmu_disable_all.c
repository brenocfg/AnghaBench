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
struct cpu_hw_events {int /*<<< orphan*/  active_mask; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_pmu_wait_on_overflow (int) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 scalar_t__ in_nmi () ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_disable_all () ; 

__attribute__((used)) static void amd_pmu_disable_all(void)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int idx;

	x86_pmu_disable_all();

	/*
	 * This shouldn't be called from NMI context, but add a safeguard here
	 * to return, since if we're in NMI context we can't wait for an NMI
	 * to reset an overflowed counter value.
	 */
	if (in_nmi())
		return;

	/*
	 * Check each counter for overflow and wait for it to be reset by the
	 * NMI if it has overflowed. This relies on the fact that all active
	 * counters are always enabled when this function is caled and
	 * ARCH_PERFMON_EVENTSEL_INT is always set.
	 */
	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		if (!test_bit(idx, cpuc->active_mask))
			continue;

		amd_pmu_wait_on_overflow(idx);
	}
}