#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* chip; } ;
struct irq_desc {TYPE_3__ irq_data; } ;
struct grpci1_priv {int /*<<< orphan*/ * irq_map; int /*<<< orphan*/  irq_err; TYPE_2__* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* irq_eoi ) (TYPE_3__*) ;} ;

/* Variables and functions */
 unsigned int IRQ_ALL_ERRORS ; 
 unsigned int IRQ_INTX ; 
 unsigned int IRQ_MASK_BIT ; 
 unsigned int REGLOAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct grpci1_priv* grpci1priv ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void grpci1_pci_flow_irq(struct irq_desc *desc)
{
	struct grpci1_priv *priv = grpci1priv;
	int i, ack = 0;
	unsigned int irqreg;

	irqreg = REGLOAD(priv->regs->irq);
	irqreg = (irqreg >> IRQ_MASK_BIT) & irqreg;

	/* Error Interrupt? */
	if (irqreg & IRQ_ALL_ERRORS) {
		generic_handle_irq(priv->irq_err);
		ack = 1;
	}

	/* PCI Interrupt? */
	if (irqreg & IRQ_INTX) {
		/* Call respective PCI Interrupt handler */
		for (i = 0; i < 4; i++) {
			if (irqreg & (1 << i))
				generic_handle_irq(priv->irq_map[i]);
		}
		ack = 1;
	}

	/*
	 * Call "first level" IRQ chip end-of-irq handler. It will ACK LEON IRQ
	 * Controller, this must be done after IRQ sources have been handled to
	 * avoid double IRQ generation
	 */
	if (ack)
		desc->irq_data.chip->irq_eoi(&desc->irq_data);
}