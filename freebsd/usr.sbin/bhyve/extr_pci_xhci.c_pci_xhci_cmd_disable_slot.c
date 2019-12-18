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
typedef  scalar_t__ uint32_t ;
struct pci_xhci_softc {scalar_t__ ndevices; int /*<<< orphan*/ * portregs; } ;
struct pci_xhci_dev_emu {scalar_t__ dev_slotstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 struct pci_xhci_dev_emu* XHCI_SLOTDEV_PTR (struct pci_xhci_softc*,scalar_t__) ; 
 scalar_t__ XHCI_ST_DISABLED ; 
 scalar_t__ XHCI_TRB_ERROR_NO_SLOTS ; 
 scalar_t__ XHCI_TRB_ERROR_SLOT_NOT_ON ; 
 scalar_t__ XHCI_TRB_ERROR_SUCCESS ; 

__attribute__((used)) static uint32_t
pci_xhci_cmd_disable_slot(struct pci_xhci_softc *sc, uint32_t slot)
{
	struct pci_xhci_dev_emu *dev;
	uint32_t cmderr;

	DPRINTF(("pci_xhci disable slot %u\r\n", slot));

	cmderr = XHCI_TRB_ERROR_NO_SLOTS;
	if (sc->portregs == NULL)
		goto done;

	if (slot > sc->ndevices) {
		cmderr = XHCI_TRB_ERROR_SLOT_NOT_ON;
		goto done;
	}

	dev = XHCI_SLOTDEV_PTR(sc, slot);
	if (dev) {
		if (dev->dev_slotstate == XHCI_ST_DISABLED) {
			cmderr = XHCI_TRB_ERROR_SLOT_NOT_ON;
		} else {
			dev->dev_slotstate = XHCI_ST_DISABLED;
			cmderr = XHCI_TRB_ERROR_SUCCESS;
			/* TODO: reset events and endpoints */
		}
	}

done:
	return (cmderr);
}