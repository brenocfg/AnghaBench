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
struct hw_perf_event {int idx; int state; scalar_t__ event_base_rdpmc; scalar_t__ event_base; scalar_t__ config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct amd_uncore {int num_counters; scalar_t__ rdpmc_base; scalar_t__ msr_base; struct perf_event** events; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  amd_uncore_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmpxchg (struct perf_event**,int /*<<< orphan*/ *,struct perf_event*) ; 
 struct amd_uncore* event_to_amd_uncore (struct perf_event*) ; 

__attribute__((used)) static int amd_uncore_add(struct perf_event *event, int flags)
{
	int i;
	struct amd_uncore *uncore = event_to_amd_uncore(event);
	struct hw_perf_event *hwc = &event->hw;

	/* are we already assigned? */
	if (hwc->idx != -1 && uncore->events[hwc->idx] == event)
		goto out;

	for (i = 0; i < uncore->num_counters; i++) {
		if (uncore->events[i] == event) {
			hwc->idx = i;
			goto out;
		}
	}

	/* if not, take the first available counter */
	hwc->idx = -1;
	for (i = 0; i < uncore->num_counters; i++) {
		if (cmpxchg(&uncore->events[i], NULL, event) == NULL) {
			hwc->idx = i;
			break;
		}
	}

out:
	if (hwc->idx == -1)
		return -EBUSY;

	hwc->config_base = uncore->msr_base + (2 * hwc->idx);
	hwc->event_base = uncore->msr_base + 1 + (2 * hwc->idx);
	hwc->event_base_rdpmc = uncore->rdpmc_base + hwc->idx;
	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	if (flags & PERF_EF_START)
		amd_uncore_start(event, PERF_EF_RELOAD);

	return 0;
}