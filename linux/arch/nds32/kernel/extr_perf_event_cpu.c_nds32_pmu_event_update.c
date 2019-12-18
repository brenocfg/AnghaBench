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
typedef  scalar_t__ u64 ;
struct hw_perf_event {int /*<<< orphan*/  period_left; int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  count; struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct nds32_pmu {scalar_t__ (* read_counter ) (struct perf_event*) ;scalar_t__ max_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct perf_event*) ; 
 struct nds32_pmu* to_nds32_pmu (int /*<<< orphan*/ ) ; 

u64 nds32_pmu_event_update(struct perf_event *event)
{
	struct nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	u64 delta, prev_raw_count, new_raw_count;

again:
	prev_raw_count = local64_read(&hwc->prev_count);
	new_raw_count = nds32_pmu->read_counter(event);

	if (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			    new_raw_count) != prev_raw_count) {
		goto again;
	}
	/*
	 * Whether overflow or not, "unsigned substraction"
	 * will always get their delta
	 */
	delta = (new_raw_count - prev_raw_count) & nds32_pmu->max_period;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	return new_raw_count;
}