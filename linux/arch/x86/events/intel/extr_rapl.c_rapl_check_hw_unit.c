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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_RAPL_POWER_UNIT ; 
 int NR_RAPL_DOMAINS ; 
 size_t PERF_RAPL_RAM ; 
 int* rapl_hw_unit ; 
 unsigned long long rapl_timer_ms ; 
 scalar_t__ rdmsrl_safe (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int rapl_check_hw_unit(bool apply_quirk)
{
	u64 msr_rapl_power_unit_bits;
	int i;

	/* protect rdmsrl() to handle virtualization */
	if (rdmsrl_safe(MSR_RAPL_POWER_UNIT, &msr_rapl_power_unit_bits))
		return -1;
	for (i = 0; i < NR_RAPL_DOMAINS; i++)
		rapl_hw_unit[i] = (msr_rapl_power_unit_bits >> 8) & 0x1FULL;

	/*
	 * DRAM domain on HSW server and KNL has fixed energy unit which can be
	 * different than the unit from power unit MSR. See
	 * "Intel Xeon Processor E5-1600 and E5-2600 v3 Product Families, V2
	 * of 2. Datasheet, September 2014, Reference Number: 330784-001 "
	 */
	if (apply_quirk)
		rapl_hw_unit[PERF_RAPL_RAM] = 16;

	/*
	 * Calculate the timer rate:
	 * Use reference of 200W for scaling the timeout to avoid counter
	 * overflows. 200W = 200 Joules/sec
	 * Divide interval by 2 to avoid lockstep (2 * 100)
	 * if hw unit is 32, then we use 2 ms 1/200/2
	 */
	rapl_timer_ms = 2;
	if (rapl_hw_unit[0] < 32) {
		rapl_timer_ms = (1000 / (2 * 100));
		rapl_timer_ms *= (1ULL << (32 - rapl_hw_unit[0] - 1));
	}
	return 0;
}