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
struct perf_event {int /*<<< orphan*/  pmu; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {scalar_t__ ed; scalar_t__ es; } ;
struct cpu_hw_sf {int /*<<< orphan*/  handle; int /*<<< orphan*/ * event; int /*<<< orphan*/  flags; TYPE_1__ lsctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  PMU_F_IN_USE ; 
 scalar_t__ SAMPL_DIAG_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aux_output_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_hw_sf ; 
 int /*<<< orphan*/  cpumsf_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 struct cpu_hw_sf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumsf_pmu_del(struct perf_event *event, int flags)
{
	struct cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);

	perf_pmu_disable(event->pmu);
	cpumsf_pmu_stop(event, PERF_EF_UPDATE);

	cpuhw->lsctl.es = 0;
	cpuhw->lsctl.ed = 0;
	cpuhw->flags &= ~PMU_F_IN_USE;
	cpuhw->event = NULL;

	if (SAMPL_DIAG_MODE(&event->hw))
		aux_output_end(&cpuhw->handle);
	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
}