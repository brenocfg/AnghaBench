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
typedef  int u32 ;
struct hw_perf_event {int idx; int config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int ARMV8_PMUV3_PERFCTR_CHAIN ; 
 int ARMV8_PMU_INCLUDE_EL2 ; 
 scalar_t__ armv8pmu_event_is_chained (struct perf_event*) ; 
 int /*<<< orphan*/  armv8pmu_write_evtype (int,int) ; 

__attribute__((used)) static inline void armv8pmu_write_event_type(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	/*
	 * For chained events, the low counter is programmed to count
	 * the event of interest and the high counter is programmed
	 * with CHAIN event code with filters set to count at all ELs.
	 */
	if (armv8pmu_event_is_chained(event)) {
		u32 chain_evt = ARMV8_PMUV3_PERFCTR_CHAIN |
				ARMV8_PMU_INCLUDE_EL2;

		armv8pmu_write_evtype(idx - 1, hwc->config_base);
		armv8pmu_write_evtype(idx, chain_evt);
	} else {
		armv8pmu_write_evtype(idx, hwc->config_base);
	}
}