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
struct mpc52xx_gpt_priv {int /*<<< orphan*/  lock; TYPE_1__* regs; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPC52xx_GPT_MODE_IRQ_EN ; 
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mpc52xx_gpt_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mpc52xx_gpt_irq_mask(struct irq_data *d)
{
	struct mpc52xx_gpt_priv *gpt = irq_data_get_irq_chip_data(d);
	unsigned long flags;

	raw_spin_lock_irqsave(&gpt->lock, flags);
	clrbits32(&gpt->regs->mode, MPC52xx_GPT_MODE_IRQ_EN);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);
}