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
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  event_update (struct perf_event*) ; 

__attribute__((used)) static void pmu_event_stop(struct perf_event *event, int mode)
{
	struct hw_perf_event *hwc = &event->hw;

	/* Mark event as deactivated and stopped. */
	if (!(hwc->state & PERF_HES_STOPPED))
		hwc->state |= PERF_HES_STOPPED;

	/* Check if software counter update is necessary. */
	if ((mode & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) {
		/*
		 * Drain the remaining delta count out of an event
		 * that we are disabling:
		 */
		event_update(event);
		hwc->state |= PERF_HES_UPTODATE;
	}
}