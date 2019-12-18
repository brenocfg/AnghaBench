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
struct nlm_pic_irq {TYPE_1__* node; int /*<<< orphan*/  irt; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  piclock; int /*<<< orphan*/  picbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct nlm_pic_irq* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  nlm_pic_disable_irt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xlp_pic_disable(struct irq_data *d)
{
	struct nlm_pic_irq *pd = irq_data_get_irq_chip_data(d);
	unsigned long flags;

	BUG_ON(!pd);
	spin_lock_irqsave(&pd->node->piclock, flags);
	nlm_pic_disable_irt(pd->node->picbase, pd->irt);
	spin_unlock_irqrestore(&pd->node->piclock, flags);
}