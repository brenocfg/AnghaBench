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
typedef  unsigned long long u64 ;
struct perf_event {int dummy; } ;
struct hw_perf_event {unsigned long long sample_period; unsigned long long last_period; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  period_left; } ;
struct TYPE_2__ {unsigned long long max_period; unsigned long long overflow; int /*<<< orphan*/  (* write_counter ) (int,unsigned long long) ;} ;

/* Variables and functions */
 unsigned long long local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,unsigned long long) ; 
 TYPE_1__ mipspmu ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (int,unsigned long long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mipspmu_event_set_period(struct perf_event *event,
				    struct hw_perf_event *hwc,
				    int idx)
{
	u64 left = local64_read(&hwc->period_left);
	u64 period = hwc->sample_period;
	int ret = 0;

	if (unlikely((left + period) & (1ULL << 63))) {
		/* left underflowed by more than period. */
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	} else	if (unlikely((left + period) <= period)) {
		/* left underflowed by less than period. */
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	}

	if (left > mipspmu.max_period) {
		left = mipspmu.max_period;
		local64_set(&hwc->period_left, left);
	}

	local64_set(&hwc->prev_count, mipspmu.overflow - left);

	mipspmu.write_counter(idx, mipspmu.overflow - left);

	perf_event_update_userpage(event);

	return ret;
}