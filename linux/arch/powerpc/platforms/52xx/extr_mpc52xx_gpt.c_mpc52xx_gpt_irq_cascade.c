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
typedef  int u32 ;
struct mpc52xx_gpt_priv {int /*<<< orphan*/  irqhost; TYPE_1__* regs; } ;
struct irq_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int MPC52xx_GPT_STATUS_IRQMASK ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 struct mpc52xx_gpt_priv* irq_desc_get_handler_data (struct irq_desc*) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc52xx_gpt_irq_cascade(struct irq_desc *desc)
{
	struct mpc52xx_gpt_priv *gpt = irq_desc_get_handler_data(desc);
	int sub_virq;
	u32 status;

	status = in_be32(&gpt->regs->status) & MPC52xx_GPT_STATUS_IRQMASK;
	if (status) {
		sub_virq = irq_linear_revmap(gpt->irqhost, 0);
		generic_handle_irq(sub_virq);
	}
}