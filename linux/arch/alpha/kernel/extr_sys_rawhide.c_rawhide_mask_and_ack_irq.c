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
typedef  unsigned int* vuip ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCPCIA_HOSE2MID (unsigned int) ; 
 scalar_t__ MCPCIA_INT_REQ (int /*<<< orphan*/ ) ; 
 unsigned int* cached_irq_masks ; 
 int /*<<< orphan*/  hose_exists (unsigned int) ; 
 unsigned int* hose_irq_masks ; 
 int /*<<< orphan*/  rawhide_irq_lock ; 
 int /*<<< orphan*/  rawhide_update_irq_hw (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rawhide_mask_and_ack_irq(struct irq_data *d)
{
	unsigned int mask, mask1, hose;
	unsigned int irq = d->irq;

	irq -= 16;
	hose = irq / 24;
	if (!hose_exists(hose)) /* if hose non-existent, exit */
		return;

	irq -= hose * 24;
	mask1 = 1 << irq;
	mask = ~mask1 | hose_irq_masks[hose];

	spin_lock(&rawhide_irq_lock);

	mask &= cached_irq_masks[hose];
	cached_irq_masks[hose] = mask;
	rawhide_update_irq_hw(hose, mask);

	/* Clear the interrupt.  */
	*(vuip)MCPCIA_INT_REQ(MCPCIA_HOSE2MID(hose)) = mask1;

	spin_unlock(&rawhide_irq_lock);
}