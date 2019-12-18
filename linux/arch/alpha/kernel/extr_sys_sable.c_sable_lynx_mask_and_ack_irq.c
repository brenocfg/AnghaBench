#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {size_t irq; } ;
struct TYPE_2__ {unsigned long* irq_to_mask; unsigned long shadow_mask; int /*<<< orphan*/  (* ack_irq_hw ) (unsigned long) ;int /*<<< orphan*/  (* update_irq_hw ) (unsigned long,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sable_lynx_irq_lock ; 
 TYPE_1__* sable_lynx_irq_swizzle ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  stub2 (unsigned long) ; 

__attribute__((used)) static void
sable_lynx_mask_and_ack_irq(struct irq_data *d)
{
	unsigned long bit, mask;

	bit = sable_lynx_irq_swizzle->irq_to_mask[d->irq];
	spin_lock(&sable_lynx_irq_lock);
	mask = sable_lynx_irq_swizzle->shadow_mask |= 1UL << bit;
	sable_lynx_irq_swizzle->update_irq_hw(bit, mask);
	sable_lynx_irq_swizzle->ack_irq_hw(bit);
	spin_unlock(&sable_lynx_irq_lock);
}