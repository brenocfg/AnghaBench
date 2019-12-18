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
 int /*<<< orphan*/  CPU_FTR_P9_TLBIE_ERAT_BUG ; 
 int /*<<< orphan*/  CPU_FTR_P9_TLBIE_STQ_BUG ; 
 int /*<<< orphan*/  MMU_PAGE_64K ; 
 int /*<<< orphan*/  RIC_FLUSH_TLB ; 
 int /*<<< orphan*/  __tlbie_lpid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tlbie_lpid_va (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_get_ap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fixup_tlbie_lpid(unsigned long lpid)
{
	/*
	 * We can use any address for the invalidation, pick one which is
	 * probably unused as an optimisation.
	 */
	unsigned long va = ((1UL << 52) - 1);

	if (cpu_has_feature(CPU_FTR_P9_TLBIE_ERAT_BUG)) {
		asm volatile("ptesync": : :"memory");
		__tlbie_lpid(0, RIC_FLUSH_TLB);
	}

	if (cpu_has_feature(CPU_FTR_P9_TLBIE_STQ_BUG)) {
		asm volatile("ptesync": : :"memory");
		__tlbie_lpid_va(va, lpid, mmu_get_ap(MMU_PAGE_64K), RIC_FLUSH_TLB);
	}
}