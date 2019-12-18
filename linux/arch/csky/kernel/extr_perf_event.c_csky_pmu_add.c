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
struct pmu_hw_events {struct perf_event** events; } ;
struct hw_perf_event {size_t idx; int state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 TYPE_1__ csky_pmu ; 
 int /*<<< orphan*/  csky_pmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct pmu_hw_events* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csky_pmu_add(struct perf_event *event, int flags)
{
	struct pmu_hw_events *hw_events = this_cpu_ptr(csky_pmu.hw_events);
	struct hw_perf_event *hwc = &event->hw;

	hw_events->events[hwc->idx] = event;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	if (flags & PERF_EF_START)
		csky_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);

	return 0;
}