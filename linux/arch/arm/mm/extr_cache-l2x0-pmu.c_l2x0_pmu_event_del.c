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
struct hw_perf_event {size_t idx; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/ ** events ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2x0_pmu_event_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2x0_pmu_hrtimer ; 
 scalar_t__ l2x0_pmu_num_active_counters () ; 

__attribute__((used)) static void l2x0_pmu_event_del(struct perf_event *event, int flags)
{
	struct hw_perf_event *hw = &event->hw;

	l2x0_pmu_event_stop(event, PERF_EF_UPDATE);

	events[hw->idx] = NULL;
	hw->idx = -1;

	if (l2x0_pmu_num_active_counters() == 0)
		hrtimer_cancel(&l2x0_pmu_hrtimer);
}