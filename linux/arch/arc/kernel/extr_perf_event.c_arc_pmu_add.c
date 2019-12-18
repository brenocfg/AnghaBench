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
struct hw_perf_event {int idx; int state; int /*<<< orphan*/  prev_count; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct arc_pmu_cpu {struct perf_event** act_counter; int /*<<< orphan*/ * used_mask; } ;
struct TYPE_2__ {int n_counters; int /*<<< orphan*/  max_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_PCT_CONFIG ; 
 int /*<<< orphan*/  ARC_REG_PCT_COUNTH ; 
 int /*<<< orphan*/  ARC_REG_PCT_COUNTL ; 
 int /*<<< orphan*/  ARC_REG_PCT_INDEX ; 
 int /*<<< orphan*/  ARC_REG_PCT_INT_CNTH ; 
 int /*<<< orphan*/  ARC_REG_PCT_INT_CNTL ; 
 int EAGAIN ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* arc_pmu ; 
 int /*<<< orphan*/  arc_pmu_cpu ; 
 int /*<<< orphan*/  arc_pmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int ffz (int /*<<< orphan*/ ) ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct arc_pmu_cpu* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int arc_pmu_add(struct perf_event *event, int flags)
{
	struct arc_pmu_cpu *pmu_cpu = this_cpu_ptr(&arc_pmu_cpu);
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	idx = ffz(pmu_cpu->used_mask[0]);
	if (idx == arc_pmu->n_counters)
		return -EAGAIN;

	__set_bit(idx, pmu_cpu->used_mask);
	hwc->idx = idx;

	write_aux_reg(ARC_REG_PCT_INDEX, idx);

	pmu_cpu->act_counter[idx] = event;

	if (is_sampling_event(event)) {
		/* Mimic full counter overflow as other arches do */
		write_aux_reg(ARC_REG_PCT_INT_CNTL,
			      lower_32_bits(arc_pmu->max_period));
		write_aux_reg(ARC_REG_PCT_INT_CNTH,
			      upper_32_bits(arc_pmu->max_period));
	}

	write_aux_reg(ARC_REG_PCT_CONFIG, 0);
	write_aux_reg(ARC_REG_PCT_COUNTL, 0);
	write_aux_reg(ARC_REG_PCT_COUNTH, 0);
	local64_set(&hwc->prev_count, 0);

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	if (flags & PERF_EF_START)
		arc_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);

	return 0;
}