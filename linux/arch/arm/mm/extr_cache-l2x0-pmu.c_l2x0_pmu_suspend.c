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

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int PMU_NR_COUNTERS ; 
 scalar_t__* events ; 
 int /*<<< orphan*/  l2x0_pmu ; 
 int /*<<< orphan*/  l2x0_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2x0_pmu_event_stop (scalar_t__,int /*<<< orphan*/ ) ; 

void l2x0_pmu_suspend(void)
{
	int i;

	if (!l2x0_pmu)
		return;

	l2x0_pmu_disable(l2x0_pmu);

	for (i = 0; i < PMU_NR_COUNTERS; i++) {
		if (events[i])
			l2x0_pmu_event_stop(events[i], PERF_EF_UPDATE);
	}

}