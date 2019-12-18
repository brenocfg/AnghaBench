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
typedef  int /*<<< orphan*/  u32 ;
struct perf_event_attr {int dummy; } ;
struct hw_perf_event {int idx; } ;
struct perf_event {struct perf_event_attr attr; struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMV8_IDX_TO_COUNTER (int) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armv8pmu_disable_counter (int) ; 
 scalar_t__ armv8pmu_event_is_chained (struct perf_event*) ; 
 int /*<<< orphan*/  kvm_clr_pmu_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pmu_counter_deferred (struct perf_event_attr*) ; 

__attribute__((used)) static inline void armv8pmu_disable_event_counter(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct perf_event_attr *attr = &event->attr;
	int idx = hwc->idx;
	u32 counter_bits = BIT(ARMV8_IDX_TO_COUNTER(idx));

	if (armv8pmu_event_is_chained(event))
		counter_bits |= BIT(ARMV8_IDX_TO_COUNTER(idx - 1));

	kvm_clr_pmu_events(counter_bits);

	/* We rely on the hypervisor switch code to disable guest counters */
	if (!kvm_pmu_counter_deferred(attr)) {
		if (armv8pmu_event_is_chained(event))
			armv8pmu_disable_counter(idx - 1);
		armv8pmu_disable_counter(idx);
	}
}