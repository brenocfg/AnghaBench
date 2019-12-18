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
 int /*<<< orphan*/  local_flush_tlb_from (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ r3k_have_wired_reg ; 
 int read_c0_wired () ; 

void local_flush_tlb_all(void)
{
	unsigned long flags;

#ifdef DEBUG_TLB
	printk("[tlball]");
#endif
	local_irq_save(flags);
	local_flush_tlb_from(r3k_have_wired_reg ? read_c0_wired() : 8);
	local_irq_restore(flags);
}