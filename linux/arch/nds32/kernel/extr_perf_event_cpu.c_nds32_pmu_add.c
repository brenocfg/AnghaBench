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
struct pmu_hw_events {struct perf_event** events; } ;
struct hw_perf_event {int idx; int state; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;
struct nds32_pmu {int (* get_event_idx ) (struct pmu_hw_events*,struct perf_event*) ;int /*<<< orphan*/  (* disable ) (struct perf_event*) ;struct pmu_hw_events* (* get_hw_events ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  nds32_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 struct pmu_hw_events* stub1 () ; 
 int stub2 (struct pmu_hw_events*,struct perf_event*) ; 
 int /*<<< orphan*/  stub3 (struct perf_event*) ; 
 struct nds32_pmu* to_nds32_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nds32_pmu_add(struct perf_event *event, int flags)
{
	struct nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	struct pmu_hw_events *hw_events = nds32_pmu->get_hw_events();
	struct hw_perf_event *hwc = &event->hw;
	int idx;
	int err = 0;

	perf_pmu_disable(event->pmu);

	/* If we don't have a space for the counter then finish early. */
	idx = nds32_pmu->get_event_idx(hw_events, event);
	if (idx < 0) {
		err = idx;
		goto out;
	}

	/*
	 * If there is an event in the counter we are going to use then make
	 * sure it is disabled.
	 */
	event->hw.idx = idx;
	nds32_pmu->disable(event);
	hw_events->events[idx] = event;

	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	if (flags & PERF_EF_START)
		nds32_start(event, PERF_EF_RELOAD);

	/* Propagate our changes to the userspace mapping. */
	perf_event_update_userpage(event);

out:
	perf_pmu_enable(event->pmu);
	return err;
}