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
struct TYPE_2__ {unsigned long config_base; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 unsigned long ARMV8_PMUV3_PERFCTR_CHAIN ; 
 unsigned long ARMV8_PMU_EVTYPE_EVENT ; 

__attribute__((used)) static int armv8pmu_filter_match(struct perf_event *event)
{
	unsigned long evtype = event->hw.config_base & ARMV8_PMU_EVTYPE_EVENT;
	return evtype != ARMV8_PMUV3_PERFCTR_CHAIN;
}