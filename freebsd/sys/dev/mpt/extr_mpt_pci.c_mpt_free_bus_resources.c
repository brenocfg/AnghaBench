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
struct mpt_softc {int /*<<< orphan*/ * pci_reg; int /*<<< orphan*/  dev; int /*<<< orphan*/ * pci_pio_reg; int /*<<< orphan*/ * pci_irq; int /*<<< orphan*/ * ih; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mpt_free_bus_resources(struct mpt_softc *mpt)
{

	if (mpt->ih) {
		bus_teardown_intr(mpt->dev, mpt->pci_irq, mpt->ih);
		mpt->ih = NULL;
	}

	if (mpt->pci_irq) {
		bus_release_resource(mpt->dev, SYS_RES_IRQ,
		    rman_get_rid(mpt->pci_irq), mpt->pci_irq);
		pci_release_msi(mpt->dev);
		mpt->pci_irq = NULL;
	}

	if (mpt->pci_pio_reg) {
		bus_release_resource(mpt->dev, SYS_RES_IOPORT,
		    rman_get_rid(mpt->pci_pio_reg), mpt->pci_pio_reg);
		mpt->pci_pio_reg = NULL;
	}

	if (mpt->pci_reg) {
		bus_release_resource(mpt->dev, SYS_RES_MEMORY,
		    rman_get_rid(mpt->pci_reg), mpt->pci_reg);
		mpt->pci_reg = NULL;
	}
}