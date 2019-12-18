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
struct uic {int /*<<< orphan*/  lock; scalar_t__ dcrbase; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ UIC_ER ; 
 scalar_t__ UIC_SR ; 
 struct uic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_is_level_type (struct irq_data*) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int mfdcr (scalar_t__) ; 
 int /*<<< orphan*/  mtdcr (scalar_t__,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void uic_mask_ack_irq(struct irq_data *d)
{
	struct uic *uic = irq_data_get_irq_chip_data(d);
	unsigned int src = irqd_to_hwirq(d);
	unsigned long flags;
	u32 er, sr;

	sr = 1 << (31-src);
	raw_spin_lock_irqsave(&uic->lock, flags);
	er = mfdcr(uic->dcrbase + UIC_ER);
	er &= ~sr;
	mtdcr(uic->dcrbase + UIC_ER, er);
 	/* On the UIC, acking (i.e. clearing the SR bit)
	 * a level irq will have no effect if the interrupt
	 * is still asserted by the device, even if
	 * the interrupt is already masked. Therefore
	 * we only ack the egde interrupts here, while
	 * level interrupts are ack'ed after the actual
	 * isr call in the uic_unmask_irq()
	 */
	if (!irqd_is_level_type(d))
		mtdcr(uic->dcrbase + UIC_SR, sr);
	raw_spin_unlock_irqrestore(&uic->lock, flags);
}