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
struct usb_bus {int dummy; } ;
struct atmegadci_softc {int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 struct atmegadci_softc* ATMEGA_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atmegadci_interrupt_poll (struct atmegadci_softc*) ; 

__attribute__((used)) static void
atmegadci_do_poll(struct usb_bus *bus)
{
	struct atmegadci_softc *sc = ATMEGA_BUS2SC(bus);

	USB_BUS_LOCK(&sc->sc_bus);
	atmegadci_interrupt_poll(sc);
	USB_BUS_UNLOCK(&sc->sc_bus);
}