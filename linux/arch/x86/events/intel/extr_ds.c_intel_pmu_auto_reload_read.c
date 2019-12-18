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
struct TYPE_2__ {int flags; } ;
struct perf_event {int /*<<< orphan*/  pmu; TYPE_1__ hw; } ;

/* Variables and functions */
 int PERF_X86_EVENT_AUTO_RELOAD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  intel_pmu_drain_pebs_buffer () ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 

void intel_pmu_auto_reload_read(struct perf_event *event)
{
	WARN_ON(!(event->hw.flags & PERF_X86_EVENT_AUTO_RELOAD));

	perf_pmu_disable(event->pmu);
	intel_pmu_drain_pebs_buffer();
	perf_pmu_enable(event->pmu);
}