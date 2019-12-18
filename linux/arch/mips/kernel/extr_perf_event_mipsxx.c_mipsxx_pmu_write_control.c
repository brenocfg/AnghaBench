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

/* Variables and functions */
 unsigned int mipsxx_pmu_swizzle_perf_idx (unsigned int) ; 
 int /*<<< orphan*/  write_c0_perfctrl0 (unsigned int) ; 
 int /*<<< orphan*/  write_c0_perfctrl1 (unsigned int) ; 
 int /*<<< orphan*/  write_c0_perfctrl2 (unsigned int) ; 
 int /*<<< orphan*/  write_c0_perfctrl3 (unsigned int) ; 

__attribute__((used)) static void mipsxx_pmu_write_control(unsigned int idx, unsigned int val)
{
	idx = mipsxx_pmu_swizzle_perf_idx(idx);

	switch (idx) {
	case 0:
		write_c0_perfctrl0(val);
		return;
	case 1:
		write_c0_perfctrl1(val);
		return;
	case 2:
		write_c0_perfctrl2(val);
		return;
	case 3:
		write_c0_perfctrl3(val);
		return;
	}
}