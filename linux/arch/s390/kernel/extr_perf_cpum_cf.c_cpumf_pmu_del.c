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
struct TYPE_2__ {size_t config_base; } ;
struct perf_event {TYPE_1__ hw; } ;
struct cpu_cf_events {int /*<<< orphan*/  state; int /*<<< orphan*/ * ctr_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 int /*<<< orphan*/  cpumf_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctr_set_disable (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumf_pmu_del(struct perf_event *event, int flags)
{
	struct cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	cpumf_pmu_stop(event, PERF_EF_UPDATE);

	/* Check if any counter in the counter set is still used.  If not used,
	 * change the counter set to the disabled state.  This also clears the
	 * content of all counters in the set.
	 *
	 * When a new perf event has been added but not yet started, this can
	 * clear enable control and resets all counters in a set.  Therefore,
	 * cpumf_pmu_start() always has to reenable a counter set.
	 */
	if (!atomic_read(&cpuhw->ctr_set[event->hw.config_base]))
		ctr_set_disable(&cpuhw->state, event->hw.config_base);

	perf_event_update_userpage(event);
}