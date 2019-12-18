#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hw_perf_event {int idx; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct event_constraint {int flags; unsigned long* idxmsk; int /*<<< orphan*/  weight; } ;
struct cpu_hw_events {int n_events; int txn_flags; struct event_constraint** event_constraint; struct perf_event** event_list; TYPE_1__* excl_cntrs; int /*<<< orphan*/  is_fake; scalar_t__ n_txn; } ;
struct TYPE_4__ {int num_counters; int /*<<< orphan*/  (* stop_scheduling ) (struct cpu_hw_events*) ;int /*<<< orphan*/  (* put_event_constraints ) (struct cpu_hw_events*,struct perf_event*) ;int /*<<< orphan*/  (* commit_scheduling ) (struct cpu_hw_events*,int,int) ;struct event_constraint* (* get_event_constraints ) (struct cpu_hw_events*,int,struct perf_event*) ;int /*<<< orphan*/  (* start_scheduling ) (struct cpu_hw_events*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  exclusive_present; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int EINVAL ; 
 int PERF_PMU_TXN_ADD ; 
 int PERF_X86_EVENT_DYNAMIC ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int X86_PMC_IDX_MAX ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int) ; 
 scalar_t__ is_ht_workaround_enabled () ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int perf_assign_events (struct event_constraint**,int,int,int,int,int*) ; 
 int /*<<< orphan*/  stub1 (struct cpu_hw_events*) ; 
 struct event_constraint* stub2 (struct cpu_hw_events*,int,struct perf_event*) ; 
 int /*<<< orphan*/  stub3 (struct cpu_hw_events*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct cpu_hw_events*,struct perf_event*) ; 
 int /*<<< orphan*/  stub5 (struct cpu_hw_events*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 TYPE_2__ x86_pmu ; 

int x86_schedule_events(struct cpu_hw_events *cpuc, int n, int *assign)
{
	struct event_constraint *c;
	unsigned long used_mask[BITS_TO_LONGS(X86_PMC_IDX_MAX)];
	struct perf_event *e;
	int n0, i, wmin, wmax, unsched = 0;
	struct hw_perf_event *hwc;

	bitmap_zero(used_mask, X86_PMC_IDX_MAX);

	/*
	 * Compute the number of events already present; see x86_pmu_add(),
	 * validate_group() and x86_pmu_commit_txn(). For the former two
	 * cpuc->n_events hasn't been updated yet, while for the latter
	 * cpuc->n_txn contains the number of events added in the current
	 * transaction.
	 */
	n0 = cpuc->n_events;
	if (cpuc->txn_flags & PERF_PMU_TXN_ADD)
		n0 -= cpuc->n_txn;

	if (x86_pmu.start_scheduling)
		x86_pmu.start_scheduling(cpuc);

	for (i = 0, wmin = X86_PMC_IDX_MAX, wmax = 0; i < n; i++) {
		c = cpuc->event_constraint[i];

		/*
		 * Previously scheduled events should have a cached constraint,
		 * while new events should not have one.
		 */
		WARN_ON_ONCE((c && i >= n0) || (!c && i < n0));

		/*
		 * Request constraints for new events; or for those events that
		 * have a dynamic constraint -- for those the constraint can
		 * change due to external factors (sibling state, allow_tfa).
		 */
		if (!c || (c->flags & PERF_X86_EVENT_DYNAMIC)) {
			c = x86_pmu.get_event_constraints(cpuc, i, cpuc->event_list[i]);
			cpuc->event_constraint[i] = c;
		}

		wmin = min(wmin, c->weight);
		wmax = max(wmax, c->weight);
	}

	/*
	 * fastpath, try to reuse previous register
	 */
	for (i = 0; i < n; i++) {
		hwc = &cpuc->event_list[i]->hw;
		c = cpuc->event_constraint[i];

		/* never assigned */
		if (hwc->idx == -1)
			break;

		/* constraint still honored */
		if (!test_bit(hwc->idx, c->idxmsk))
			break;

		/* not already used */
		if (test_bit(hwc->idx, used_mask))
			break;

		__set_bit(hwc->idx, used_mask);
		if (assign)
			assign[i] = hwc->idx;
	}

	/* slow path */
	if (i != n) {
		int gpmax = x86_pmu.num_counters;

		/*
		 * Do not allow scheduling of more than half the available
		 * generic counters.
		 *
		 * This helps avoid counter starvation of sibling thread by
		 * ensuring at most half the counters cannot be in exclusive
		 * mode. There is no designated counters for the limits. Any
		 * N/2 counters can be used. This helps with events with
		 * specific counter constraints.
		 */
		if (is_ht_workaround_enabled() && !cpuc->is_fake &&
		    READ_ONCE(cpuc->excl_cntrs->exclusive_present))
			gpmax /= 2;

		unsched = perf_assign_events(cpuc->event_constraint, n, wmin,
					     wmax, gpmax, assign);
	}

	/*
	 * In case of success (unsched = 0), mark events as committed,
	 * so we do not put_constraint() in case new events are added
	 * and fail to be scheduled
	 *
	 * We invoke the lower level commit callback to lock the resource
	 *
	 * We do not need to do all of this in case we are called to
	 * validate an event group (assign == NULL)
	 */
	if (!unsched && assign) {
		for (i = 0; i < n; i++) {
			e = cpuc->event_list[i];
			if (x86_pmu.commit_scheduling)
				x86_pmu.commit_scheduling(cpuc, i, assign[i]);
		}
	} else {
		for (i = n0; i < n; i++) {
			e = cpuc->event_list[i];

			/*
			 * release events that failed scheduling
			 */
			if (x86_pmu.put_event_constraints)
				x86_pmu.put_event_constraints(cpuc, e);

			cpuc->event_constraint[i] = NULL;
		}
	}

	if (x86_pmu.stop_scheduling)
		x86_pmu.stop_scheduling(cpuc);

	return unsched ? -EINVAL : 0;
}