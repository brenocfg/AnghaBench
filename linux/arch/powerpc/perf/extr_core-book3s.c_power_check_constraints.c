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
typedef  int /*<<< orphan*/  u64 ;
struct cpu_hw_events {unsigned long** amasks; unsigned long** avalues; int /*<<< orphan*/ ** alternatives; } ;
struct TYPE_2__ {unsigned long add_fields; unsigned long test_adder; unsigned long group_constraint_mask; unsigned long group_constraint_val; int n_counter; int (* get_alternatives ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ;scalar_t__ (* get_constraint ) (int /*<<< orphan*/ ,unsigned long*,unsigned long*) ;int /*<<< orphan*/  (* limited_pmc_event ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_HWEVENTS ; 
 unsigned int PPMU_LIMITED_PMC_REQD ; 
 TYPE_1__* ppmu ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int stub4 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 

__attribute__((used)) static int power_check_constraints(struct cpu_hw_events *cpuhw,
				   u64 event_id[], unsigned int cflags[],
				   int n_ev)
{
	unsigned long mask, value, nv;
	unsigned long smasks[MAX_HWEVENTS], svalues[MAX_HWEVENTS];
	int n_alt[MAX_HWEVENTS], choice[MAX_HWEVENTS];
	int i, j;
	unsigned long addf = ppmu->add_fields;
	unsigned long tadd = ppmu->test_adder;
	unsigned long grp_mask = ppmu->group_constraint_mask;
	unsigned long grp_val = ppmu->group_constraint_val;

	if (n_ev > ppmu->n_counter)
		return -1;

	/* First see if the events will go on as-is */
	for (i = 0; i < n_ev; ++i) {
		if ((cflags[i] & PPMU_LIMITED_PMC_REQD)
		    && !ppmu->limited_pmc_event(event_id[i])) {
			ppmu->get_alternatives(event_id[i], cflags[i],
					       cpuhw->alternatives[i]);
			event_id[i] = cpuhw->alternatives[i][0];
		}
		if (ppmu->get_constraint(event_id[i], &cpuhw->amasks[i][0],
					 &cpuhw->avalues[i][0]))
			return -1;
	}
	value = mask = 0;
	for (i = 0; i < n_ev; ++i) {
		nv = (value | cpuhw->avalues[i][0]) +
			(value & cpuhw->avalues[i][0] & addf);

		if (((((nv + tadd) ^ value) & mask) & (~grp_mask)) != 0)
			break;

		if (((((nv + tadd) ^ cpuhw->avalues[i][0]) & cpuhw->amasks[i][0])
			& (~grp_mask)) != 0)
			break;

		value = nv;
		mask |= cpuhw->amasks[i][0];
	}
	if (i == n_ev) {
		if ((value & mask & grp_mask) != (mask & grp_val))
			return -1;
		else
			return 0;	/* all OK */
	}

	/* doesn't work, gather alternatives... */
	if (!ppmu->get_alternatives)
		return -1;
	for (i = 0; i < n_ev; ++i) {
		choice[i] = 0;
		n_alt[i] = ppmu->get_alternatives(event_id[i], cflags[i],
						  cpuhw->alternatives[i]);
		for (j = 1; j < n_alt[i]; ++j)
			ppmu->get_constraint(cpuhw->alternatives[i][j],
					     &cpuhw->amasks[i][j],
					     &cpuhw->avalues[i][j]);
	}

	/* enumerate all possibilities and see if any will work */
	i = 0;
	j = -1;
	value = mask = nv = 0;
	while (i < n_ev) {
		if (j >= 0) {
			/* we're backtracking, restore context */
			value = svalues[i];
			mask = smasks[i];
			j = choice[i];
		}
		/*
		 * See if any alternative k for event_id i,
		 * where k > j, will satisfy the constraints.
		 */
		while (++j < n_alt[i]) {
			nv = (value | cpuhw->avalues[i][j]) +
				(value & cpuhw->avalues[i][j] & addf);
			if ((((nv + tadd) ^ value) & mask) == 0 &&
			    (((nv + tadd) ^ cpuhw->avalues[i][j])
			     & cpuhw->amasks[i][j]) == 0)
				break;
		}
		if (j >= n_alt[i]) {
			/*
			 * No feasible alternative, backtrack
			 * to event_id i-1 and continue enumerating its
			 * alternatives from where we got up to.
			 */
			if (--i < 0)
				return -1;
		} else {
			/*
			 * Found a feasible alternative for event_id i,
			 * remember where we got up to with this event_id,
			 * go on to the next event_id, and start with
			 * the first alternative for it.
			 */
			choice[i] = j;
			svalues[i] = value;
			smasks[i] = mask;
			value = nv;
			mask |= cpuhw->amasks[i][j];
			++i;
			j = -1;
		}
	}

	/* OK, we have a feasible combination, tell the caller the solution */
	for (i = 0; i < n_ev; ++i)
		event_id[i] = cpuhw->alternatives[i][choice[i]];
	return 0;
}