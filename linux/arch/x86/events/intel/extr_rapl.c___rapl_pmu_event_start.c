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
struct rapl_pmu {int n_active; int /*<<< orphan*/  active_list; } ;
struct TYPE_2__ {int state; int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  active_entry; } ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rapl_read_counter (struct perf_event*) ; 
 int /*<<< orphan*/  rapl_start_hrtimer (struct rapl_pmu*) ; 

__attribute__((used)) static void __rapl_pmu_event_start(struct rapl_pmu *pmu,
				   struct perf_event *event)
{
	if (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		return;

	event->hw.state = 0;

	list_add_tail(&event->active_entry, &pmu->active_list);

	local64_set(&event->hw.prev_count, rapl_read_counter(event));

	pmu->n_active++;
	if (pmu->n_active == 1)
		rapl_start_hrtimer(pmu);
}