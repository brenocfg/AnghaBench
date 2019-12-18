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
 unsigned int PNX833X_PIC_IRQ_BASE ; 
 int /*<<< orphan*/  pnx833x_hard_enable_pic_irq (unsigned int) ; 
 int /*<<< orphan*/  pnx833x_irq_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int pnx833x_startup_pic_irq(unsigned int irq)
{
	unsigned long flags;
	unsigned int pic_irq = irq - PNX833X_PIC_IRQ_BASE;

	raw_spin_lock_irqsave(&pnx833x_irq_lock, flags);
	pnx833x_hard_enable_pic_irq(pic_irq);
	raw_spin_unlock_irqrestore(&pnx833x_irq_lock, flags);
	return 0;
}