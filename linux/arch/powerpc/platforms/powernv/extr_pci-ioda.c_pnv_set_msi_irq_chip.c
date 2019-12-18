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
struct irq_chip {int /*<<< orphan*/  irq_eoi; } ;
struct TYPE_2__ {int irq_chip_init; struct irq_chip irq_chip; } ;
struct pnv_phb {scalar_t__ model; TYPE_1__ ioda; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ PNV_PHB_MODEL_PHB3 ; 
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip (unsigned int,struct irq_chip*) ; 
 int /*<<< orphan*/  pnv_ioda2_msi_eoi ; 

void pnv_set_msi_irq_chip(struct pnv_phb *phb, unsigned int virq)
{
	struct irq_data *idata;
	struct irq_chip *ichip;

	/* The MSI EOI OPAL call is only needed on PHB3 */
	if (phb->model != PNV_PHB_MODEL_PHB3)
		return;

	if (!phb->ioda.irq_chip_init) {
		/*
		 * First time we setup an MSI IRQ, we need to setup the
		 * corresponding IRQ chip to route correctly.
		 */
		idata = irq_get_irq_data(virq);
		ichip = irq_data_get_irq_chip(idata);
		phb->ioda.irq_chip_init = 1;
		phb->ioda.irq_chip = *ichip;
		phb->ioda.irq_chip.irq_eoi = pnv_ioda2_msi_eoi;
	}
	irq_set_chip(virq, &phb->ioda.irq_chip);
}