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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 unsigned int* cached_irq_masks ; 
 int /*<<< orphan*/  hose_exists (unsigned int) ; 
 int /*<<< orphan*/  rawhide_irq_lock ; 
 int /*<<< orphan*/  rawhide_update_irq_hw (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void 
rawhide_enable_irq(struct irq_data *d)
{
	unsigned int mask, hose;
	unsigned int irq = d->irq;

	irq -= 16;
	hose = irq / 24;
	if (!hose_exists(hose)) /* if hose non-existent, exit */
		return;

	irq -= hose * 24;
	mask = 1 << irq;

	spin_lock(&rawhide_irq_lock);
	mask |= cached_irq_masks[hose];
	cached_irq_masks[hose] = mask;
	rawhide_update_irq_hw(hose, mask);
	spin_unlock(&rawhide_irq_lock);
}