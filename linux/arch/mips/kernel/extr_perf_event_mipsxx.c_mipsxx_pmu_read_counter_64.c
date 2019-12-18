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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned int) ; 
 unsigned int mipsxx_pmu_swizzle_perf_idx (unsigned int) ; 
 int /*<<< orphan*/  read_c0_perfcntr0_64 () ; 
 int /*<<< orphan*/  read_c0_perfcntr1_64 () ; 
 int /*<<< orphan*/  read_c0_perfcntr2_64 () ; 
 int /*<<< orphan*/  read_c0_perfcntr3_64 () ; 

__attribute__((used)) static u64 mipsxx_pmu_read_counter_64(unsigned int idx)
{
	idx = mipsxx_pmu_swizzle_perf_idx(idx);

	switch (idx) {
	case 0:
		return read_c0_perfcntr0_64();
	case 1:
		return read_c0_perfcntr1_64();
	case 2:
		return read_c0_perfcntr2_64();
	case 3:
		return read_c0_perfcntr3_64();
	default:
		WARN_ONCE(1, "Invalid performance counter number (%d)\n", idx);
		return 0;
	}
}