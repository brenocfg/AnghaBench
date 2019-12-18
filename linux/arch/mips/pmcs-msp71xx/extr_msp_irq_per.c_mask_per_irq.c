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
struct irq_data {int irq; } ;

/* Variables and functions */
 int MSP_PER_INTBASE ; 
 int* PER_INT_MSK_REG ; 
 int /*<<< orphan*/  per_lock ; 
 int /*<<< orphan*/  per_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void mask_per_irq(struct irq_data *d)
{
#ifdef CONFIG_SMP
	unsigned long flags;
	spin_lock_irqsave(&per_lock, flags);
	*PER_INT_MSK_REG &= ~(1 << (d->irq - MSP_PER_INTBASE));
	spin_unlock_irqrestore(&per_lock, flags);
#else
	*PER_INT_MSK_REG &= ~(1 << (d->irq - MSP_PER_INTBASE));
#endif
	per_wmb();
}