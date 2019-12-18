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
struct TYPE_2__ {int idx; int state; int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  active_entry; } ;
struct intel_uncore_box {int n_active; int /*<<< orphan*/  active_mask; struct perf_event** events; int /*<<< orphan*/  active_list; } ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int UNCORE_PMC_IDX_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uncore_enable_event (struct intel_uncore_box*,struct perf_event*) ; 
 struct intel_uncore_box* uncore_event_to_box (struct perf_event*) ; 
 scalar_t__ uncore_pmc_freerunning (int) ; 
 int /*<<< orphan*/  uncore_pmu_start_hrtimer (struct intel_uncore_box*) ; 
 int /*<<< orphan*/  uncore_read_counter (struct intel_uncore_box*,struct perf_event*) ; 

void uncore_pmu_event_start(struct perf_event *event, int flags)
{
	struct intel_uncore_box *box = uncore_event_to_box(event);
	int idx = event->hw.idx;

	if (WARN_ON_ONCE(idx == -1 || idx >= UNCORE_PMC_IDX_MAX))
		return;

	/*
	 * Free running counter is read-only and always active.
	 * Use the current counter value as start point.
	 * There is no overflow interrupt for free running counter.
	 * Use hrtimer to periodically poll the counter to avoid overflow.
	 */
	if (uncore_pmc_freerunning(event->hw.idx)) {
		list_add_tail(&event->active_entry, &box->active_list);
		local64_set(&event->hw.prev_count,
			    uncore_read_counter(box, event));
		if (box->n_active++ == 0)
			uncore_pmu_start_hrtimer(box);
		return;
	}

	if (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		return;

	event->hw.state = 0;
	box->events[idx] = event;
	box->n_active++;
	__set_bit(idx, box->active_mask);

	local64_set(&event->hw.prev_count, uncore_read_counter(box, event));
	uncore_enable_event(box, event);

	if (box->n_active == 1)
		uncore_pmu_start_hrtimer(box);
}