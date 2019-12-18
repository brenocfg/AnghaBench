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
struct avr32dci_softc {int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 struct avr32dci_softc* AVR32_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avr32dci_interrupt_poll (struct avr32dci_softc*) ; 

__attribute__((used)) static void
avr32dci_do_poll(struct usb_bus *bus)
{
	struct avr32dci_softc *sc = AVR32_BUS2SC(bus);

	USB_BUS_LOCK(&sc->sc_bus);
	avr32dci_interrupt_poll(sc);
	USB_BUS_UNLOCK(&sc->sc_bus);
}