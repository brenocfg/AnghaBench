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
typedef  size_t uint8_t ;
struct TYPE_4__ {TYPE_1__* devs; } ;
struct xhci_softc {size_t sc_noslot; TYPE_2__ sc_hw; } ;
struct usb_device {size_t controller_slot_id; int /*<<< orphan*/ * parent_hub; int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_CMD_LOCK (struct xhci_softc*) ; 
 int /*<<< orphan*/  XHCI_CMD_UNLOCK (struct xhci_softc*) ; 
 int /*<<< orphan*/  XHCI_ST_DISABLED ; 
 int /*<<< orphan*/  xhci_cmd_disable_slot (struct xhci_softc*,size_t) ; 
 int /*<<< orphan*/  xhci_free_device_ext (struct usb_device*) ; 

__attribute__((used)) static void
xhci_device_uninit(struct usb_device *udev)
{
	struct xhci_softc *sc = XHCI_BUS2SC(udev->bus);
	uint8_t index;

	/* no init for root HUB */
	if (udev->parent_hub == NULL)
		return;

	XHCI_CMD_LOCK(sc);

	index = udev->controller_slot_id;

	if (index <= sc->sc_noslot) {
		xhci_cmd_disable_slot(sc, index);
		sc->sc_hw.devs[index].state = XHCI_ST_DISABLED;

		/* free device extension */
		xhci_free_device_ext(udev);
	}

	XHCI_CMD_UNLOCK(sc);
}