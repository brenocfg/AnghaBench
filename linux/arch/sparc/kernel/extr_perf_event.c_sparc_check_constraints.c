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
typedef  int u8 ;
struct TYPE_3__ {int idx; } ;
struct perf_event {TYPE_1__ hw; } ;
struct TYPE_4__ {int max_hw_events; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PIC_LOWER ; 
 int PIC_UPPER ; 
 int SPARC_PMU_HAS_CONFLICTS ; 
 int perf_event_get_msk (unsigned long) ; 
 TYPE_2__* sparc_pmu ; 

__attribute__((used)) static int sparc_check_constraints(struct perf_event **evts,
				   unsigned long *events, int n_ev)
{
	u8 msk0 = 0, msk1 = 0;
	int idx0 = 0;

	/* This case is possible when we are invoked from
	 * hw_perf_group_sched_in().
	 */
	if (!n_ev)
		return 0;

	if (n_ev > sparc_pmu->max_hw_events)
		return -1;

	if (!(sparc_pmu->flags & SPARC_PMU_HAS_CONFLICTS)) {
		int i;

		for (i = 0; i < n_ev; i++)
			evts[i]->hw.idx = i;
		return 0;
	}

	msk0 = perf_event_get_msk(events[0]);
	if (n_ev == 1) {
		if (msk0 & PIC_LOWER)
			idx0 = 1;
		goto success;
	}
	BUG_ON(n_ev != 2);
	msk1 = perf_event_get_msk(events[1]);

	/* If both events can go on any counter, OK.  */
	if (msk0 == (PIC_UPPER | PIC_LOWER) &&
	    msk1 == (PIC_UPPER | PIC_LOWER))
		goto success;

	/* If one event is limited to a specific counter,
	 * and the other can go on both, OK.
	 */
	if ((msk0 == PIC_UPPER || msk0 == PIC_LOWER) &&
	    msk1 == (PIC_UPPER | PIC_LOWER)) {
		if (msk0 & PIC_LOWER)
			idx0 = 1;
		goto success;
	}

	if ((msk1 == PIC_UPPER || msk1 == PIC_LOWER) &&
	    msk0 == (PIC_UPPER | PIC_LOWER)) {
		if (msk1 & PIC_UPPER)
			idx0 = 1;
		goto success;
	}

	/* If the events are fixed to different counters, OK.  */
	if ((msk0 == PIC_UPPER && msk1 == PIC_LOWER) ||
	    (msk0 == PIC_LOWER && msk1 == PIC_UPPER)) {
		if (msk0 & PIC_LOWER)
			idx0 = 1;
		goto success;
	}

	/* Otherwise, there is a conflict.  */
	return -1;

success:
	evts[0]->hw.idx = idx0;
	if (n_ev == 2)
		evts[1]->hw.idx = idx0 ^ 1;
	return 0;
}