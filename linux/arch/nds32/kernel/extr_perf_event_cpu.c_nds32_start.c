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
struct hw_perf_event {int state; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct nds32_pmu {int /*<<< orphan*/  (* enable ) (struct perf_event*) ;} ;

/* Variables and functions */
 int PERF_EF_RELOAD ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  nds32_pmu_event_set_period (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 struct nds32_pmu* to_nds32_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nds32_start(struct perf_event *event, int flags)
{
	struct nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	/*
	 * NDS pmu always has to reprogram the period, so ignore
	 * PERF_EF_RELOAD, see the comment below.
	 */
	if (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;
	/* Set the period for the event. */
	nds32_pmu_event_set_period(event);

	nds32_pmu->enable(event);
}