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
struct cpu_hw_events {int* saved_ctrl; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 int M_PERFCTL_COUNT_EVENT_WHENEVER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ mipspmu ; 
 int mipsxx_pmu_read_control (int) ; 
 int /*<<< orphan*/  mipsxx_pmu_write_control (int,int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mipsxx_pmu_disable_event(int idx)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	unsigned long flags;

	WARN_ON(idx < 0 || idx >= mipspmu.num_counters);

	local_irq_save(flags);
	cpuc->saved_ctrl[idx] = mipsxx_pmu_read_control(idx) &
		~M_PERFCTL_COUNT_EVENT_WHENEVER;
	mipsxx_pmu_write_control(idx, cpuc->saved_ctrl[idx]);
	local_irq_restore(flags);
}