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
struct pmu_hw_events {int /*<<< orphan*/  used_mask; } ;
struct hw_perf_event {unsigned long config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int EAGAIN ; 
 int NDS32_IDX_COUNTER0 ; 
 int NDS32_IDX_COUNTER1 ; 
 int NDS32_IDX_CYCLE_COUNTER ; 
 unsigned long SOFTWARE_EVENT_MASK ; 
 unsigned long SPAV3_0_SEL_TOTAL_CYCLES ; 
 unsigned long SPAV3_1_SEL_COMPLETED_INSTRUCTION ; 
 int get_converted_event_idx (unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nds32_pmu_get_event_idx(struct pmu_hw_events *cpuc,
				   struct perf_event *event)
{
	int idx;
	struct hw_perf_event *hwc = &event->hw;
	/*
	 * Current implementation maps cycles, instruction count and cache-miss
	 * to specific counter.
	 * However, multiple of the 3 counters are able to count these events.
	 *
	 *
	 * SOFTWARE_EVENT_MASK mask for getting event num ,
	 * This is defined by Jia-Rung, you can change the polocies.
	 * However, do not exceed 8 bits. This is hardware specific.
	 * The last number is SPAv3_2_SEL_LAST.
	 */
	unsigned long evtype = hwc->config_base & SOFTWARE_EVENT_MASK;

	idx = get_converted_event_idx(evtype);
	/*
	 * Try to get the counter for correpsonding event
	 */
	if (evtype == SPAV3_0_SEL_TOTAL_CYCLES) {
		if (!test_and_set_bit(idx, cpuc->used_mask))
			return idx;
		if (!test_and_set_bit(NDS32_IDX_COUNTER0, cpuc->used_mask))
			return NDS32_IDX_COUNTER0;
		if (!test_and_set_bit(NDS32_IDX_COUNTER1, cpuc->used_mask))
			return NDS32_IDX_COUNTER1;
	} else if (evtype == SPAV3_1_SEL_COMPLETED_INSTRUCTION) {
		if (!test_and_set_bit(idx, cpuc->used_mask))
			return idx;
		else if (!test_and_set_bit(NDS32_IDX_COUNTER1, cpuc->used_mask))
			return NDS32_IDX_COUNTER1;
		else if (!test_and_set_bit
			 (NDS32_IDX_CYCLE_COUNTER, cpuc->used_mask))
			return NDS32_IDX_CYCLE_COUNTER;
	} else {
		if (!test_and_set_bit(idx, cpuc->used_mask))
			return idx;
	}
	return -EAGAIN;
}