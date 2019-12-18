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
 int MMU_ITLB_ADDRESS_ARRAY ; 
 int MMU_ITLB_ADDRESS_ARRAY2 ; 
 int MMU_PAGE_ASSOC_BIT ; 
 int MMU_UTLB_ADDRESS_ARRAY ; 
 int MMU_UTLB_ADDRESS_ARRAY2 ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int) ; 
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 

void local_flush_tlb_one(unsigned long asid, unsigned long page)
{
	jump_to_uncached();
	__raw_writel(page, MMU_UTLB_ADDRESS_ARRAY | MMU_PAGE_ASSOC_BIT);
	__raw_writel(asid, MMU_UTLB_ADDRESS_ARRAY2 | MMU_PAGE_ASSOC_BIT);
	__raw_writel(page, MMU_ITLB_ADDRESS_ARRAY | MMU_PAGE_ASSOC_BIT);
	__raw_writel(asid, MMU_ITLB_ADDRESS_ARRAY2 | MMU_PAGE_ASSOC_BIT);
	back_to_cached();
}