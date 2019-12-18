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
struct TYPE_2__ {int r_irq_rid; int /*<<< orphan*/  handle; int /*<<< orphan*/  r_irq; } ;
struct siis_controller {int quirks; TYPE_1__ irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_INTR_FLAGS ; 
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SIIS_Q_NOMSI ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct siis_controller*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct siis_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_msi_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  siis_intr ; 

__attribute__((used)) static int
siis_setup_interrupt(device_t dev)
{
	struct siis_controller *ctlr = device_get_softc(dev);
	int msi = ctlr->quirks & SIIS_Q_NOMSI ? 0 : 1;

	/* Process hints. */
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "msi", &msi);
	if (msi < 0)
		msi = 0;
	else if (msi > 0)
		msi = min(1, pci_msi_count(dev));
	/* Allocate MSI if needed/present. */
	if (msi && pci_alloc_msi(dev, &msi) != 0)
		msi = 0;
	/* Allocate all IRQs. */
	ctlr->irq.r_irq_rid = msi ? 1 : 0;
	if (!(ctlr->irq.r_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &ctlr->irq.r_irq_rid, RF_SHAREABLE | RF_ACTIVE))) {
		device_printf(dev, "unable to map interrupt\n");
		return ENXIO;
	}
	if ((bus_setup_intr(dev, ctlr->irq.r_irq, ATA_INTR_FLAGS, NULL,
	    siis_intr, ctlr, &ctlr->irq.handle))) {
		/* SOS XXX release r_irq */
		device_printf(dev, "unable to setup interrupt\n");
		return ENXIO;
	}
	return (0);
}