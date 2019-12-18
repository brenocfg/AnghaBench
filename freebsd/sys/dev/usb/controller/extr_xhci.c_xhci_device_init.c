#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
typedef  size_t uint8_t ;
struct TYPE_3__ {TYPE_2__* devs; } ;
struct xhci_softc {size_t sc_noslot; TYPE_1__ sc_hw; } ;
struct usb_device {size_t controller_slot_id; int /*<<< orphan*/ * parent_hub; int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,size_t) ; 
 scalar_t__ USB_ERR_BAD_ADDRESS ; 
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_CMD_LOCK (struct xhci_softc*) ; 
 int /*<<< orphan*/  XHCI_CMD_UNLOCK (struct xhci_softc*) ; 
 scalar_t__ XHCI_ST_DISABLED ; 
 scalar_t__ XHCI_ST_ENABLED ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xhci_alloc_device_ext (struct usb_device*) ; 
 scalar_t__ xhci_cmd_enable_slot (struct xhci_softc*,size_t*) ; 
 scalar_t__ xhci_set_address (struct usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
xhci_device_init(struct usb_device *udev)
{
	struct xhci_softc *sc = XHCI_BUS2SC(udev->bus);
	usb_error_t err;
	uint8_t temp;

	/* no init for root HUB */
	if (udev->parent_hub == NULL)
		return (0);

	XHCI_CMD_LOCK(sc);

	/* set invalid default */

	udev->controller_slot_id = sc->sc_noslot + 1;

	/* try to get a new slot ID from the XHCI */

	err = xhci_cmd_enable_slot(sc, &temp);

	if (err) {
		XHCI_CMD_UNLOCK(sc);
		return (err);
	}

	if (temp > sc->sc_noslot) {
		XHCI_CMD_UNLOCK(sc);
		return (USB_ERR_BAD_ADDRESS);
	}

	if (sc->sc_hw.devs[temp].state != XHCI_ST_DISABLED) {
		DPRINTF("slot %u already allocated.\n", temp);
		XHCI_CMD_UNLOCK(sc);
		return (USB_ERR_BAD_ADDRESS);
	}

	/* store slot ID for later reference */

	udev->controller_slot_id = temp;

	/* reset data structure */

	memset(&sc->sc_hw.devs[temp], 0, sizeof(sc->sc_hw.devs[0]));

	/* set mark slot allocated */

	sc->sc_hw.devs[temp].state = XHCI_ST_ENABLED;

	err = xhci_alloc_device_ext(udev);

	XHCI_CMD_UNLOCK(sc);

	/* get device into default state */

	if (err == 0)
		err = xhci_set_address(udev, NULL, 0);

	return (err);
}