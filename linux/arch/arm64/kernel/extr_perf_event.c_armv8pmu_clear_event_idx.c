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
struct pmu_hw_events {int /*<<< orphan*/  used_mask; } ;
struct TYPE_2__ {int idx; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ armv8pmu_event_is_chained (struct perf_event*) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armv8pmu_clear_event_idx(struct pmu_hw_events *cpuc,
				     struct perf_event *event)
{
	int idx = event->hw.idx;

	clear_bit(idx, cpuc->used_mask);
	if (armv8pmu_event_is_chained(event))
		clear_bit(idx - 1, cpuc->used_mask);
}