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
struct xtensa_pmu_events {struct perf_event** event; int /*<<< orphan*/  used_mask; } ;
struct hw_perf_event {int idx; int state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int XCHAL_NUM_PERF_COUNTERS ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ __test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct xtensa_pmu_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xtensa_pmu_events ; 
 int /*<<< orphan*/  xtensa_pmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xtensa_pmu_add(struct perf_event *event, int flags)
{
	struct xtensa_pmu_events *ev = this_cpu_ptr(&xtensa_pmu_events);
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (__test_and_set_bit(idx, ev->used_mask)) {
		idx = find_first_zero_bit(ev->used_mask,
					  XCHAL_NUM_PERF_COUNTERS);
		if (idx == XCHAL_NUM_PERF_COUNTERS)
			return -EAGAIN;

		__set_bit(idx, ev->used_mask);
		hwc->idx = idx;
	}
	ev->event[idx] = event;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	if (flags & PERF_EF_START)
		xtensa_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);
	return 0;
}