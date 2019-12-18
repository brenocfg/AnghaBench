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
typedef  int u32 ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ GEF_PIC_INTR_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ gef_pic_irq_reg_base ; 
 int /*<<< orphan*/  gef_pic_lock ; 
 int in_be32 (scalar_t__) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gef_pic_mask(struct irq_data *d)
{
	unsigned long flags;
	unsigned int hwirq = irqd_to_hwirq(d);
	u32 mask;

	raw_spin_lock_irqsave(&gef_pic_lock, flags);
	mask = in_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0));
	mask &= ~(1 << hwirq);
	out_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0), mask);
	raw_spin_unlock_irqrestore(&gef_pic_lock, flags);
}