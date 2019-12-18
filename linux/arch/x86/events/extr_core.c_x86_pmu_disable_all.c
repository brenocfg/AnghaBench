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
typedef  int u64 ;
struct cpu_hw_events {int /*<<< orphan*/  active_mask; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 int ARCH_PERFMON_EVENTSEL_ENABLE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_config_addr (int) ; 

void x86_pmu_disable_all(void)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int idx;

	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		u64 val;

		if (!test_bit(idx, cpuc->active_mask))
			continue;
		rdmsrl(x86_pmu_config_addr(idx), val);
		if (!(val & ARCH_PERFMON_EVENTSEL_ENABLE))
			continue;
		val &= ~ARCH_PERFMON_EVENTSEL_ENABLE;
		wrmsrl(x86_pmu_config_addr(idx), val);
	}
}