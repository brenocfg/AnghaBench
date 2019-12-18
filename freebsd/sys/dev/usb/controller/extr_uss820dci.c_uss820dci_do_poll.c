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
struct uss820dci_softc {int /*<<< orphan*/  sc_bus; } ;
struct usb_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 struct uss820dci_softc* USS820_DCI_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  uss820dci_interrupt_complete_locked (struct uss820dci_softc*) ; 
 int /*<<< orphan*/  uss820dci_interrupt_poll_locked (struct uss820dci_softc*) ; 

__attribute__((used)) static void
uss820dci_do_poll(struct usb_bus *bus)
{
	struct uss820dci_softc *sc = USS820_DCI_BUS2SC(bus);

	USB_BUS_LOCK(&sc->sc_bus);
	USB_BUS_SPIN_LOCK(&sc->sc_bus);
	uss820dci_interrupt_poll_locked(sc);
	uss820dci_interrupt_complete_locked(sc);
	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
	USB_BUS_UNLOCK(&sc->sc_bus);
}