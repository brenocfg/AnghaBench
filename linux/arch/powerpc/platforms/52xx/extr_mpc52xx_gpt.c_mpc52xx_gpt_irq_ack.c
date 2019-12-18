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
struct mpc52xx_gpt_priv {TYPE_1__* regs; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPC52xx_GPT_STATUS_IRQMASK ; 
 struct mpc52xx_gpt_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc52xx_gpt_irq_ack(struct irq_data *d)
{
	struct mpc52xx_gpt_priv *gpt = irq_data_get_irq_chip_data(d);

	out_be32(&gpt->regs->status, MPC52xx_GPT_STATUS_IRQMASK);
}