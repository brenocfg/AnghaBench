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
typedef  int u64 ;
struct perf_event {int /*<<< orphan*/  count; } ;
struct hw_perf_event {int /*<<< orphan*/  period_left; int /*<<< orphan*/  prev_count; } ;
typedef  int s64 ;
struct TYPE_2__ {int (* read_pmc ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  local64_add (int,int /*<<< orphan*/ *) ; 
 int local64_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_sub (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* sparc_pmu ; 
 int stub1 (int) ; 

__attribute__((used)) static u64 sparc_perf_event_update(struct perf_event *event,
				   struct hw_perf_event *hwc, int idx)
{
	int shift = 64 - 32;
	u64 prev_raw_count, new_raw_count;
	s64 delta;

again:
	prev_raw_count = local64_read(&hwc->prev_count);
	new_raw_count = sparc_pmu->read_pmc(idx);

	if (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			     new_raw_count) != prev_raw_count)
		goto again;

	delta = (new_raw_count << shift) - (prev_raw_count << shift);
	delta >>= shift;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	return new_raw_count;
}