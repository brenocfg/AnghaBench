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
struct xhci_softc {int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,void*,struct xhci_softc*) ; 
 int /*<<< orphan*/  xhci_interrupt (struct xhci_softc*) ; 

__attribute__((used)) static void
xhci_interrupt_poll(void *_sc)
{
	struct xhci_softc *sc = _sc;
	USB_BUS_UNLOCK(&sc->sc_bus);
	xhci_interrupt(sc);
	USB_BUS_LOCK(&sc->sc_bus);
	usb_callout_reset(&sc->sc_callout, 1, (void *)&xhci_interrupt_poll, sc);
}