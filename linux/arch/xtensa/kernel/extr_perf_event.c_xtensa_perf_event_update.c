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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;
struct perf_event {int /*<<< orphan*/  count; TYPE_1__ hw; } ;
struct hw_perf_event {int /*<<< orphan*/  period_left; int /*<<< orphan*/  prev_count; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ XTENSA_PMU_COUNTER_MASK ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ xtensa_pmu_read_counter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xtensa_perf_event_update(struct perf_event *event,
				     struct hw_perf_event *hwc, int idx)
{
	uint64_t prev_raw_count, new_raw_count;
	int64_t delta;

	do {
		prev_raw_count = local64_read(&hwc->prev_count);
		new_raw_count = xtensa_pmu_read_counter(event->hw.idx);
	} while (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
				 new_raw_count) != prev_raw_count);

	delta = (new_raw_count - prev_raw_count) & XTENSA_PMU_COUNTER_MASK;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);
}