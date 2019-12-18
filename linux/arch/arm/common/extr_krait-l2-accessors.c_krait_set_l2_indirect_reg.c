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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  krait_l2_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void krait_set_l2_indirect_reg(u32 addr, u32 val)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&krait_l2_lock, flags);
	/*
	 * Select the L2 window by poking l2cpselr, then write to the window
	 * via l2cpdr.
	 */
	asm volatile ("mcr p15, 3, %0, c15, c0, 6 @ l2cpselr" : : "r" (addr));
	isb();
	asm volatile ("mcr p15, 3, %0, c15, c0, 7 @ l2cpdr" : : "r" (val));
	isb();

	raw_spin_unlock_irqrestore(&krait_l2_lock, flags);
}