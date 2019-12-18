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
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
struct xhci_softc {int dummy; } ;
struct usb_device {int controller_slot_id; int /*<<< orphan*/ * parent_hub; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_CMD_LOCK (struct xhci_softc*) ; 
 int /*<<< orphan*/  XHCI_CMD_UNLOCK (struct xhci_softc*) ; 
 int XHCI_MAX_ENDPOINTS ; 
 scalar_t__ xhci_cmd_stop_ep (struct xhci_softc*,int,int,int) ; 

__attribute__((used)) static void
xhci_device_suspend(struct usb_device *udev)
{
	struct xhci_softc *sc = XHCI_BUS2SC(udev->bus);
	uint8_t index;
	uint8_t n;
	usb_error_t err;

	DPRINTF("\n");

	/* check for root HUB */
	if (udev->parent_hub == NULL)
		return;

	index = udev->controller_slot_id;

	XHCI_CMD_LOCK(sc);

	/* blindly suspend all endpoints */

	for (n = 1; n != XHCI_MAX_ENDPOINTS; n++) {
		err = xhci_cmd_stop_ep(sc, 1, n, index);
		if (err != 0) {
			DPRINTF("Failed to suspend endpoint "
			    "%u on slot %u (ignored).\n", n, index);
		}
	}

	XHCI_CMD_UNLOCK(sc);
}