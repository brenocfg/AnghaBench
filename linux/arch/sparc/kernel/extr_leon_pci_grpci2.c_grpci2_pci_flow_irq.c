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
struct TYPE_6__ {TYPE_2__* chip; } ;
struct irq_desc {TYPE_3__ irq_data; } ;
struct grpci2_priv {scalar_t__ irq_mode; int /*<<< orphan*/  virq_dma; int /*<<< orphan*/ * irq_map; int /*<<< orphan*/  virq_err; TYPE_1__* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* irq_eoi ) (TYPE_3__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  sts_cap; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 unsigned int CTRL_HOSTINT ; 
 unsigned int REGLOAD (int /*<<< orphan*/ ) ; 
 unsigned int STS_ERR_IRQ ; 
 unsigned int STS_IDMA ; 
 unsigned int STS_IDMAERR ; 
 unsigned int STS_INTSTS_BIT ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct grpci2_priv* grpci2priv ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void grpci2_pci_flow_irq(struct irq_desc *desc)
{
	struct grpci2_priv *priv = grpci2priv;
	int i, ack = 0;
	unsigned int ctrl, sts_cap, pci_ints;

	ctrl = REGLOAD(priv->regs->ctrl);
	sts_cap = REGLOAD(priv->regs->sts_cap);

	/* Error Interrupt? */
	if (sts_cap & STS_ERR_IRQ) {
		generic_handle_irq(priv->virq_err);
		ack = 1;
	}

	/* PCI Interrupt? */
	pci_ints = ((~sts_cap) >> STS_INTSTS_BIT) & ctrl & CTRL_HOSTINT;
	if (pci_ints) {
		/* Call respective PCI Interrupt handler */
		for (i = 0; i < 4; i++) {
			if (pci_ints & (1 << i))
				generic_handle_irq(priv->irq_map[i]);
		}
		ack = 1;
	}

	/*
	 * Decode DMA Interrupt only when shared with Err and PCI INTX#, when
	 * the DMA is a unique IRQ the DMA interrupts doesn't end up here, they
	 * goes directly to DMA ISR.
	 */
	if ((priv->irq_mode == 0) && (sts_cap & (STS_IDMA | STS_IDMAERR))) {
		generic_handle_irq(priv->virq_dma);
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