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
struct TYPE_2__ {int state; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int /*<<< orphan*/  hw_perf_event_update (struct perf_event*) ; 

__attribute__((used)) static void cpumf_pmu_read(struct perf_event *event)
{
	if (event->hw.state & PERF_HES_STOPPED)
		return;

	hw_perf_event_update(event);
}