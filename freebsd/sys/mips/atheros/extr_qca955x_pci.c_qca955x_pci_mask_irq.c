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
typedef  int uint32_t ;
struct ar71xx_pci_softc {scalar_t__ sc_pci_ctrl_base; } ;
struct ar71xx_pci_irq {scalar_t__ irq; struct ar71xx_pci_softc* sc; } ;

/* Variables and functions */
 scalar_t__ AR71XX_PCI_IRQ_START ; 
 int ATH_READ_REG (scalar_t__) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (scalar_t__,int) ; 
 int QCA955X_PCI_INTR_DEV0 ; 
 scalar_t__ QCA955X_PCI_INTR_MASK ; 
 scalar_t__ QCA955X_PCI_INTR_STATUS ; 

__attribute__((used)) static void
qca955x_pci_mask_irq(void *source)
{
	uint32_t reg;
	struct ar71xx_pci_irq *pirq = source;
	struct ar71xx_pci_softc *sc = pirq->sc;

	/* XXX - Only one interrupt ? Only one device ? */
	if (pirq->irq != AR71XX_PCI_IRQ_START)
		return;

	/* Update the interrupt mask reg */
	reg = ATH_READ_REG(sc->sc_pci_ctrl_base + QCA955X_PCI_INTR_MASK);
	ATH_WRITE_REG(sc->sc_pci_ctrl_base + QCA955X_PCI_INTR_MASK,
	    reg & ~QCA955X_PCI_INTR_DEV0);

	/* Clear any pending interrupt */
	reg = ATH_READ_REG(sc->sc_pci_ctrl_base + QCA955X_PCI_INTR_STATUS);
	ATH_WRITE_REG(sc->sc_pci_ctrl_base + QCA955X_PCI_INTR_STATUS,
	    reg | QCA955X_PCI_INTR_DEV0);
}