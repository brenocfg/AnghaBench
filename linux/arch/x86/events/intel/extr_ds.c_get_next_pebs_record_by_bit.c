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
struct cpu_hw_events {unsigned long pebs_enabled; int /*<<< orphan*/  pebs_record_size; } ;
struct TYPE_3__ {int pebs_format; } ;
struct TYPE_4__ {TYPE_1__ intel_cap; } ;

/* Variables and functions */
 int PEBS_COUNTER_MASK ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 unsigned long get_pebs_status (void*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static inline void *
get_next_pebs_record_by_bit(void *base, void *top, int bit)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	void *at;
	u64 pebs_status;

	/*
	 * fmt0 does not have a status bitfield (does not use
	 * perf_record_nhm format)
	 */
	if (x86_pmu.intel_cap.pebs_format < 1)
		return base;

	if (base == NULL)
		return NULL;

	for (at = base; at < top; at += cpuc->pebs_record_size) {
		unsigned long status = get_pebs_status(at);

		if (test_bit(bit, (unsigned long *)&status)) {
			/* PEBS v3 has accurate status bits */
			if (x86_pmu.intel_cap.pebs_format >= 3)
				return at;

			if (status == (1 << bit))
				return at;

			/* clear non-PEBS bit and re-check */
			pebs_status = status & cpuc->pebs_enabled;
			pebs_status &= PEBS_COUNTER_MASK;
			if (pebs_status == (1 << bit))
				return at;
		}
	}
	return NULL;
}