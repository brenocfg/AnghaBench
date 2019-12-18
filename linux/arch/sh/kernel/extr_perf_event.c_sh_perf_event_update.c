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
struct hw_perf_event {int /*<<< orphan*/  prev_count; } ;
typedef  int s64 ;
struct TYPE_2__ {int (* read ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  local64_add (int,int /*<<< orphan*/ *) ; 
 int local64_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* sh_pmu ; 
 int stub1 (int) ; 

__attribute__((used)) static void sh_perf_event_update(struct perf_event *event,
				   struct hw_perf_event *hwc, int idx)
{
	u64 prev_raw_count, new_raw_count;
	s64 delta;
	int shift = 0;

	/*
	 * Depending on the counter configuration, they may or may not
	 * be chained, in which case the previous counter value can be
	 * updated underneath us if the lower-half overflows.
	 *
	 * Our tactic to handle this is to first atomically read and
	 * exchange a new raw count - then add that new-prev delta
	 * count to the generic counter atomically.
	 *
	 * As there is no interrupt associated with the overflow events,
	 * this is the simplest approach for maintaining consistency.
	 */
again:
	prev_raw_count = local64_read(&hwc->prev_count);
	new_raw_count = sh_pmu->read(idx);

	if (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			     new_raw_count) != prev_raw_count)
		goto again;

	/*
	 * Now we have the new raw value and have updated the prev
	 * timestamp already. We can now calculate the elapsed delta
	 * (counter-)time and add that to the generic counter.
	 *
	 * Careful, not all hw sign-extends above the physical width
	 * of the count.
	 */
	delta = (new_raw_count << shift) - (prev_raw_count << shift);
	delta >>= shift;

	local64_add(delta, &event->count);
}