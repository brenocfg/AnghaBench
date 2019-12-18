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
struct hw_perf_event {int state; int /*<<< orphan*/  idx; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  mipspmu_event_update (struct perf_event*,struct hw_perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipsxx_pmu_disable_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mipspmu_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;

	if (!(hwc->state & PERF_HES_STOPPED)) {
		/* We are working on a local event. */
		mipsxx_pmu_disable_event(hwc->idx);
		barrier();
		mipspmu_event_update(event, hwc, hwc->idx);
		hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
	}
}