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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MMUCR ; 
 unsigned long MMUCR_URB ; 
 int MMUCR_URB_NENTRIES ; 
 unsigned long MMUCR_URB_SHIFT ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_barrier () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void tlb_unwire_entry(void)
{
	unsigned long status, flags;
	int urb;

	local_irq_save(flags);

	status = __raw_readl(MMUCR);
	urb = (status & MMUCR_URB) >> MMUCR_URB_SHIFT;
	status &= ~MMUCR_URB;

	/*
	 * Make sure we're not trying to unwire a TLB entry when none
	 * have been wired.
	 */
	BUG_ON(urb++ == MMUCR_URB_NENTRIES);

	urb = urb % MMUCR_URB_NENTRIES;

	status |= (urb << MMUCR_URB_SHIFT);
	__raw_writel(status, MMUCR);
	ctrl_barrier();

	local_irq_restore(flags);
}