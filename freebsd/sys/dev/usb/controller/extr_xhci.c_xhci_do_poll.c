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
struct xhci_softc {int /*<<< orphan*/  sc_bus; } ;
struct usb_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 struct xhci_softc* XHCI_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  xhci_interrupt_poll (struct xhci_softc*) ; 

__attribute__((used)) static void
xhci_do_poll(struct usb_bus *bus)
{
	struct xhci_softc *sc = XHCI_BUS2SC(bus);

	USB_BUS_LOCK(&sc->sc_bus);
	xhci_interrupt_poll(sc);
	USB_BUS_UNLOCK(&sc->sc_bus);
}