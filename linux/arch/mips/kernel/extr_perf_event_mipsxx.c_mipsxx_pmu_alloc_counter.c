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
struct hw_perf_event {int event_base; } ;
struct cpu_hw_events {int /*<<< orphan*/  used_mask; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 int EAGAIN ; 
 TYPE_1__ mipspmu ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static int mipsxx_pmu_alloc_counter(struct cpu_hw_events *cpuc,
				    struct hw_perf_event *hwc)
{
	int i;

	/*
	 * We only need to care the counter mask. The range has been
	 * checked definitely.
	 */
	unsigned long cntr_mask = (hwc->event_base >> 8) & 0xffff;

	for (i = mipspmu.num_counters - 1; i >= 0; i--) {
		/*
		 * Note that some MIPS perf events can be counted by both
		 * even and odd counters, wheresas many other are only by
		 * even _or_ odd counters. This introduces an issue that
		 * when the former kind of event takes the counter the
		 * latter kind of event wants to use, then the "counter
		 * allocation" for the latter event will fail. In fact if
		 * they can be dynamically swapped, they both feel happy.
		 * But here we leave this issue alone for now.
		 */
		if (test_bit(i, &cntr_mask) &&
			!test_and_set_bit(i, cpuc->used_mask))
			return i;
	}

	return -EAGAIN;
}