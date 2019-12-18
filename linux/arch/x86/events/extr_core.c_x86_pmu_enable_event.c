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
struct perf_event {int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_PERFMON_EVENTSEL_ENABLE ; 
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __x86_pmu_enable_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ cpu_hw_events ; 

void x86_pmu_enable_event(struct perf_event *event)
{
	if (__this_cpu_read(cpu_hw_events.enabled))
		__x86_pmu_enable_event(&event->hw,
				       ARCH_PERFMON_EVENTSEL_ENABLE);
}