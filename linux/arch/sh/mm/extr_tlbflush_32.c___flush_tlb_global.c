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
 int MMUCR_TI ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void __flush_tlb_global(void)
{
	unsigned long flags;

	local_irq_save(flags);

	/*
	 * This is the most destructive of the TLB flushing options,
	 * and will tear down all of the UTLB/ITLB mappings, including
	 * wired entries.
	 */
	__raw_writel(__raw_readl(MMUCR) | MMUCR_TI, MMUCR);

	local_irq_restore(flags);
}