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
struct hw_perf_event {int state; size_t config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_cf_events {int /*<<< orphan*/  state; int /*<<< orphan*/ * ctr_set; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 int /*<<< orphan*/  ctr_set_stop (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  hw_perf_event_update (struct perf_event*) ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumf_pmu_stop(struct perf_event *event, int flags)
{
	struct cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	struct hw_perf_event *hwc = &event->hw;

	if (!(hwc->state & PERF_HES_STOPPED)) {
		/* Decrement reference count for this counter set and if this
		 * is the last used counter in the set, clear activation
		 * control and set the counter set state to inactive.
		 */
		if (!atomic_dec_return(&cpuhw->ctr_set[hwc->config_base]))
			ctr_set_stop(&cpuhw->state, hwc->config_base);
		event->hw.state |= PERF_HES_STOPPED;
	}

	if ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) {
		hw_perf_event_update(event);
		event->hw.state |= PERF_HES_UPTODATE;
	}
}