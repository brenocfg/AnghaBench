#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct hw_perf_event {int sample_period; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  event_base_rdpmc; } ;
struct perf_event {int /*<<< orphan*/  count; struct hw_perf_event hw; } ;
typedef  int s64 ;
struct TYPE_4__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int cntval_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_2__ cpu_hw_events ; 
 int /*<<< orphan*/  local64_add (int,int /*<<< orphan*/ *) ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  rdpmcl (int /*<<< orphan*/ ,int) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int
intel_pmu_save_and_restart_reload(struct perf_event *event, int count)
{
	struct hw_perf_event *hwc = &event->hw;
	int shift = 64 - x86_pmu.cntval_bits;
	u64 period = hwc->sample_period;
	u64 prev_raw_count, new_raw_count;
	s64 new, old;

	WARN_ON(!period);

	/*
	 * drain_pebs() only happens when the PMU is disabled.
	 */
	WARN_ON(this_cpu_read(cpu_hw_events.enabled));

	prev_raw_count = local64_read(&hwc->prev_count);
	rdpmcl(hwc->event_base_rdpmc, new_raw_count);
	local64_set(&hwc->prev_count, new_raw_count);

	/*
	 * Since the counter increments a negative counter value and
	 * overflows on the sign switch, giving the interval:
	 *
	 *   [-period, 0]
	 *
	 * the difference between two consequtive reads is:
	 *
	 *   A) value2 - value1;
	 *      when no overflows have happened in between,
	 *
	 *   B) (0 - value1) + (value2 - (-period));
	 *      when one overflow happened in between,
	 *
	 *   C) (0 - value1) + (n - 1) * (period) + (value2 - (-period));
	 *      when @n overflows happened in between.
	 *
	 * Here A) is the obvious difference, B) is the extension to the
	 * discrete interval, where the first term is to the top of the
	 * interval and the second term is from the bottom of the next
	 * interval and C) the extension to multiple intervals, where the
	 * middle term is the whole intervals covered.
	 *
	 * An equivalent of C, by reduction, is:
	 *
	 *   value2 - value1 + n * period
	 */
	new = ((s64)(new_raw_count << shift) >> shift);
	old = ((s64)(prev_raw_count << shift) >> shift);
	local64_add(new - old + count * period, &event->count);

	perf_event_update_userpage(event);

	return 0;
}