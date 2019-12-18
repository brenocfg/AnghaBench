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
struct hw_perf_event {int idx; int state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  XTENSA_PMU_PMCTRL (int) ; 
 int /*<<< orphan*/  XTENSA_PMU_PMSTAT (int) ; 
 int /*<<< orphan*/  get_er (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_er (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtensa_perf_event_update (struct perf_event*,struct hw_perf_event*,int) ; 

__attribute__((used)) static void xtensa_pmu_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (!(hwc->state & PERF_HES_STOPPED)) {
		set_er(0, XTENSA_PMU_PMCTRL(idx));
		set_er(get_er(XTENSA_PMU_PMSTAT(idx)),
		       XTENSA_PMU_PMSTAT(idx));
		hwc->state |= PERF_HES_STOPPED;
	}

	if ((flags & PERF_EF_UPDATE) &&
	    !(event->hw.state & PERF_HES_UPTODATE)) {
		xtensa_perf_event_update(event, &event->hw, idx);
		event->hw.state |= PERF_HES_UPTODATE;
	}
}