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
struct pci_xhci_softc {int dummy; } ;
struct pci_xhci_dev_emu {int /*<<< orphan*/  dev_slotstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 struct pci_xhci_dev_emu* XHCI_SLOTDEV_PTR (struct pci_xhci_softc*,int) ; 
 int /*<<< orphan*/  XHCI_ST_DISABLED ; 

__attribute__((used)) static void
pci_xhci_reset_slot(struct pci_xhci_softc *sc, int slot)
{
	struct pci_xhci_dev_emu *dev;

	dev = XHCI_SLOTDEV_PTR(sc, slot);

	if (!dev) {
		DPRINTF(("xhci reset unassigned slot (%d)?\r\n", slot));
	} else {
		dev->dev_slotstate = XHCI_ST_DISABLED;
	}

	/* TODO: reset ring buffer pointers */
}