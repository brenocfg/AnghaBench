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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct xhci_softc {TYPE_1__ sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_ERR_IOERROR ; 
 int XHCI_CMD_HCRST ; 
 int XHCI_STS_CNR ; 
 int /*<<< orphan*/  XHCI_USBCMD ; 
 int /*<<< orphan*/  XHCI_USBSTS ; 
 int XREAD4 (struct xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XWRITE4 (struct xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  oper ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

usb_error_t
xhci_reset_controller(struct xhci_softc *sc)
{
	uint32_t temp = 0;
	uint16_t i;

	DPRINTF("\n");

	/* Reset controller */
	XWRITE4(sc, oper, XHCI_USBCMD, XHCI_CMD_HCRST);

	for (i = 0; i != 100; i++) {
		usb_pause_mtx(NULL, hz / 100);
		temp = (XREAD4(sc, oper, XHCI_USBCMD) & XHCI_CMD_HCRST) |
		    (XREAD4(sc, oper, XHCI_USBSTS) & XHCI_STS_CNR);
		if (!temp)
			break;
	}

	if (temp) {
		device_printf(sc->sc_bus.parent, "Controller "
		    "reset timeout.\n");
		return (USB_ERR_IOERROR);
	}
	return (0);
}