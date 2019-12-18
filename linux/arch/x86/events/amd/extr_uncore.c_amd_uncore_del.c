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
struct hw_perf_event {int idx; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct amd_uncore {int num_counters; int /*<<< orphan*/ * events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  amd_uncore_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 struct perf_event* cmpxchg (int /*<<< orphan*/ *,struct perf_event*,int /*<<< orphan*/ *) ; 
 struct amd_uncore* event_to_amd_uncore (struct perf_event*) ; 

__attribute__((used)) static void amd_uncore_del(struct perf_event *event, int flags)
{
	int i;
	struct amd_uncore *uncore = event_to_amd_uncore(event);
	struct hw_perf_event *hwc = &event->hw;

	amd_uncore_stop(event, PERF_EF_UPDATE);

	for (i = 0; i < uncore->num_counters; i++) {
		if (cmpxchg(&uncore->events[i], event, NULL) == event)
			break;
	}

	hwc->idx = -1;
}