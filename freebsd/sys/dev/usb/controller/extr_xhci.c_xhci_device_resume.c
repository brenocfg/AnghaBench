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
typedef  scalar_t__ uint8_t ;
struct xhci_softc {int dummy; } ;
struct usb_device {scalar_t__ controller_slot_id; int /*<<< orphan*/  bus; int /*<<< orphan*/ * parent_hub; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_CMD_LOCK (struct xhci_softc*) ; 
 int /*<<< orphan*/  XHCI_CMD_UNLOCK (struct xhci_softc*) ; 
 scalar_t__ XHCI_DB_SID_SET (scalar_t__) ; 
 int /*<<< orphan*/  XHCI_DOORBELL (scalar_t__) ; 
 scalar_t__ XHCI_MAX_ENDPOINTS ; 
 scalar_t__ XHCI_MAX_STREAMS ; 
 int /*<<< orphan*/  XWRITE4 (struct xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  door ; 

__attribute__((used)) static void
xhci_device_resume(struct usb_device *udev)
{
	struct xhci_softc *sc = XHCI_BUS2SC(udev->bus);
	uint8_t index;
	uint8_t n;
	uint8_t p;

	DPRINTF("\n");

	/* check for root HUB */
	if (udev->parent_hub == NULL)
		return;

	index = udev->controller_slot_id;

	XHCI_CMD_LOCK(sc);

	/* blindly resume all endpoints */

	USB_BUS_LOCK(udev->bus);

	for (n = 1; n != XHCI_MAX_ENDPOINTS; n++) {
		for (p = 0; p != XHCI_MAX_STREAMS; p++) {
			XWRITE4(sc, door, XHCI_DOORBELL(index),
			    n | XHCI_DB_SID_SET(p));
		}
	}

	USB_BUS_UNLOCK(udev->bus);

	XHCI_CMD_UNLOCK(sc);
}