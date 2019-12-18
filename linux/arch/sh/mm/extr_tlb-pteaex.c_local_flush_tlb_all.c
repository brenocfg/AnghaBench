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
 int /*<<< orphan*/  MMUCR ; 
 unsigned long MMUCR_URB ; 
 unsigned long MMUCR_URB_NENTRIES ; 
 unsigned long MMUCR_URB_SHIFT ; 
 int MMU_ITLB_ADDRESS_ARRAY ; 
 int MMU_UTLB_ADDRESS_ARRAY ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int) ; 
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  ctrl_barrier () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void local_flush_tlb_all(void)
{
	unsigned long flags, status;
	int i;

	/*
	 * Flush all the TLB.
	 */
	local_irq_save(flags);
	jump_to_uncached();

	status = __raw_readl(MMUCR);
	status = ((status & MMUCR_URB) >> MMUCR_URB_SHIFT);

	if (status == 0)
		status = MMUCR_URB_NENTRIES;

	for (i = 0; i < status; i++)
		__raw_writel(0x0, MMU_UTLB_ADDRESS_ARRAY | (i << 8));

	for (i = 0; i < 4; i++)
		__raw_writel(0x0, MMU_ITLB_ADDRESS_ARRAY | (i << 8));

	back_to_cached();
	ctrl_barrier();
	local_irq_restore(flags);
}