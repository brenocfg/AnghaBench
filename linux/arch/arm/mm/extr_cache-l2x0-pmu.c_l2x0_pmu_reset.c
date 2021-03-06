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
 int PMU_NR_COUNTERS ; 
 int /*<<< orphan*/  __l2x0_pmu_disable () ; 
 int /*<<< orphan*/  __l2x0_pmu_event_disable (int) ; 

__attribute__((used)) static void l2x0_pmu_reset(void)
{
	int i;

	__l2x0_pmu_disable();

	for (i = 0; i < PMU_NR_COUNTERS; i++)
		__l2x0_pmu_event_disable(i);
}