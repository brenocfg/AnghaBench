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
typedef  int /*<<< orphan*/  tunable_name ;
struct TYPE_2__ {scalar_t__ intpin; int domain; int bus; int slot; int intline; } ;
struct pci_devinfo {int /*<<< orphan*/  resources; TYPE_1__ cfg; } ;
typedef  TYPE_1__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_INTLINE ; 
 int PCI_ASSIGN_INTERRUPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_INTERRUPT_VALID (int) ; 
 int PCI_INVALID_IRQ ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ TUNABLE_INT_FETCH (char*,int*) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,scalar_t__) ; 

__attribute__((used)) static void
pci_assign_interrupt(device_t bus, device_t dev, int force_route)
{
	struct pci_devinfo *dinfo = device_get_ivars(dev);
	pcicfgregs *cfg = &dinfo->cfg;
	char tunable_name[64];
	int irq;

	/* Has to have an intpin to have an interrupt. */
	if (cfg->intpin == 0)
		return;

	/* Let the user override the IRQ with a tunable. */
	irq = PCI_INVALID_IRQ;
	snprintf(tunable_name, sizeof(tunable_name),
	    "hw.pci%d.%d.%d.INT%c.irq",
	    cfg->domain, cfg->bus, cfg->slot, cfg->intpin + 'A' - 1);
	if (TUNABLE_INT_FETCH(tunable_name, &irq) && (irq >= 255 || irq <= 0))
		irq = PCI_INVALID_IRQ;

	/*
	 * If we didn't get an IRQ via the tunable, then we either use the
	 * IRQ value in the intline register or we ask the bus to route an
	 * interrupt for us.  If force_route is true, then we only use the
	 * value in the intline register if the bus was unable to assign an
	 * IRQ.
	 */
	if (!PCI_INTERRUPT_VALID(irq)) {
		if (!PCI_INTERRUPT_VALID(cfg->intline) || force_route)
			irq = PCI_ASSIGN_INTERRUPT(bus, dev);
		if (!PCI_INTERRUPT_VALID(irq))
			irq = cfg->intline;
	}

	/* If after all that we don't have an IRQ, just bail. */
	if (!PCI_INTERRUPT_VALID(irq))
		return;

	/* Update the config register if it changed. */
	if (irq != cfg->intline) {
		cfg->intline = irq;
		pci_write_config(dev, PCIR_INTLINE, irq, 1);
	}

	/* Add this IRQ as rid 0 interrupt resource. */
	resource_list_add(&dinfo->resources, SYS_RES_IRQ, 0, irq, irq, 1);
}