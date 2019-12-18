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
 int /*<<< orphan*/  CTR_DMINLINE_SHIFT ; 
 int /*<<< orphan*/  SYS_CTR_EL0 ; 
 int cpuid_feature_extract_unsigned_field (int,int /*<<< orphan*/ ) ; 
 int read_sanitised_ftr_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clean_dcache_range_nopatch(u64 start, u64 end)
{
	u64 cur, d_size, ctr_el0;

	ctr_el0 = read_sanitised_ftr_reg(SYS_CTR_EL0);
	d_size = 4 << cpuid_feature_extract_unsigned_field(ctr_el0,
							   CTR_DMINLINE_SHIFT);
	cur = start & ~(d_size - 1);
	do {
		/*
		 * We must clean+invalidate to the PoC in order to avoid
		 * Cortex-A53 errata 826319, 827319, 824069 and 819472
		 * (this corresponds to ARM64_WORKAROUND_CLEAN_CACHE)
		 */
		asm volatile("dc civac, %0" : : "r" (cur) : "memory");
	} while (cur += d_size, cur < end);
}