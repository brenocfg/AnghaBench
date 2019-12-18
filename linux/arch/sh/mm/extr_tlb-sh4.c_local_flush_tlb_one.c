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
 unsigned long MMU_PAGE_ASSOC_BIT ; 
 unsigned long MMU_UTLB_ADDRESS_ARRAY ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 

void local_flush_tlb_one(unsigned long asid, unsigned long page)
{
	unsigned long addr, data;

	/*
	 * NOTE: PTEH.ASID should be set to this MM
	 *       _AND_ we need to write ASID to the array.
	 *
	 * It would be simple if we didn't need to set PTEH.ASID...
	 */
	addr = MMU_UTLB_ADDRESS_ARRAY | MMU_PAGE_ASSOC_BIT;
	data = page | asid; /* VALID bit is off */
	jump_to_uncached();
	__raw_writel(data, addr);
	back_to_cached();
}