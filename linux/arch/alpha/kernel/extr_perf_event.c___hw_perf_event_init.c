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
struct perf_event_attr {scalar_t__ type; size_t config; } ;
struct hw_perf_event {int event_base; scalar_t__ sample_period; int /*<<< orphan*/  period_left; scalar_t__ last_period; int /*<<< orphan*/  idx; scalar_t__ config_base; } ;
struct perf_event {int /*<<< orphan*/  destroy; struct perf_event* group_leader; struct hw_perf_event hw; struct perf_event_attr attr; } ;
struct TYPE_2__ {size_t max_events; int* event_map; scalar_t__* pmc_max_period; scalar_t__ num_pmcs; int /*<<< orphan*/  (* raw_event_valid ) (size_t) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MAX_HWEVENTS ; 
 scalar_t__ PERF_TYPE_HARDWARE ; 
 scalar_t__ PERF_TYPE_HW_CACHE ; 
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  PMC_NO_INDEX ; 
 scalar_t__ alpha_check_constraints (struct perf_event**,unsigned long*,int) ; 
 TYPE_1__* alpha_pmu ; 
 int collect_events (struct perf_event*,scalar_t__,struct perf_event**,unsigned long*,int*) ; 
 int /*<<< orphan*/  hw_perf_event_destroy ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (size_t) ; 

__attribute__((used)) static int __hw_perf_event_init(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	struct hw_perf_event *hwc = &event->hw;
	struct perf_event *evts[MAX_HWEVENTS];
	unsigned long evtypes[MAX_HWEVENTS];
	int idx_rubbish_bin[MAX_HWEVENTS];
	int ev;
	int n;

	/* We only support a limited range of HARDWARE event types with one
	 * only programmable via a RAW event type.
	 */
	if (attr->type == PERF_TYPE_HARDWARE) {
		if (attr->config >= alpha_pmu->max_events)
			return -EINVAL;
		ev = alpha_pmu->event_map[attr->config];
	} else if (attr->type == PERF_TYPE_HW_CACHE) {
		return -EOPNOTSUPP;
	} else if (attr->type == PERF_TYPE_RAW) {
		if (!alpha_pmu->raw_event_valid(attr->config))
			return -EINVAL;
		ev = attr->config;
	} else {
		return -EOPNOTSUPP;
	}

	if (ev < 0) {
		return ev;
	}

	/*
	 * We place the event type in event_base here and leave calculation
	 * of the codes to programme the PMU for alpha_pmu_enable() because
	 * it is only then we will know what HW events are actually
	 * scheduled on to the PMU.  At that point the code to programme the
	 * PMU is put into config_base and the PMC to use is placed into
	 * idx.  We initialise idx (below) to PMC_NO_INDEX to indicate that
	 * it is yet to be determined.
	 */
	hwc->event_base = ev;

	/* Collect events in a group together suitable for calling
	 * alpha_check_constraints() to verify that the group as a whole can
	 * be scheduled on to the PMU.
	 */
	n = 0;
	if (event->group_leader != event) {
		n = collect_events(event->group_leader,
				alpha_pmu->num_pmcs - 1,
				evts, evtypes, idx_rubbish_bin);
		if (n < 0)
			return -EINVAL;
	}
	evtypes[n] = hwc->event_base;
	evts[n] = event;

	if (alpha_check_constraints(evts, evtypes, n + 1))
		return -EINVAL;

	/* Indicate that PMU config and idx are yet to be determined. */
	hwc->config_base = 0;
	hwc->idx = PMC_NO_INDEX;

	event->destroy = hw_perf_event_destroy;

	/*
	 * Most architectures reserve the PMU for their use at this point.
	 * As there is no existing mechanism to arbitrate usage and there
	 * appears to be no other user of the Alpha PMU we just assume
	 * that we can just use it, hence a NO-OP here.
	 *
	 * Maybe an alpha_reserve_pmu() routine should be implemented but is
	 * anything else ever going to use it?
	 */

	if (!hwc->sample_period) {
		hwc->sample_period = alpha_pmu->pmc_max_period[0];
		hwc->last_period = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	}

	return 0;
}