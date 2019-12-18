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
typedef  int uint32_t ;
struct xhci_softc {int dummy; } ;
struct usb_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
#define  USB_HW_POWER_RESUME 130 
#define  USB_HW_POWER_SHUTDOWN 129 
#define  USB_HW_POWER_SUSPEND 128 
 struct xhci_softc* XHCI_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  xhci_halt_controller (struct xhci_softc*) ; 
 int /*<<< orphan*/  xhci_reset_controller (struct xhci_softc*) ; 
 int /*<<< orphan*/  xhci_start_controller (struct xhci_softc*) ; 

__attribute__((used)) static void
xhci_set_hw_power_sleep(struct usb_bus *bus, uint32_t state)
{
	struct xhci_softc *sc = XHCI_BUS2SC(bus);

	switch (state) {
	case USB_HW_POWER_SUSPEND:
		DPRINTF("Stopping the XHCI\n");
		xhci_halt_controller(sc);
		xhci_reset_controller(sc);
		break;
	case USB_HW_POWER_SHUTDOWN:
		DPRINTF("Stopping the XHCI\n");
		xhci_halt_controller(sc);
		xhci_reset_controller(sc);
		break;
	case USB_HW_POWER_RESUME:
		DPRINTF("Starting the XHCI\n");
		xhci_start_controller(sc);
		break;
	default:
		break;
	}
}