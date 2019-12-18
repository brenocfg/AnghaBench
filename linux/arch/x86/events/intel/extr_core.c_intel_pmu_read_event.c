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
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int PERF_X86_EVENT_AUTO_RELOAD ; 
 int /*<<< orphan*/  intel_pmu_auto_reload_read (struct perf_event*) ; 
 int /*<<< orphan*/  x86_perf_event_update (struct perf_event*) ; 

__attribute__((used)) static void intel_pmu_read_event(struct perf_event *event)
{
	if (event->hw.flags & PERF_X86_EVENT_AUTO_RELOAD)
		intel_pmu_auto_reload_read(event);
	else
		x86_perf_event_update(event);
}