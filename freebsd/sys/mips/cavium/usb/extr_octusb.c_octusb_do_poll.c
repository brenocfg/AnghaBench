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
struct octusb_softc {int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 struct octusb_softc* OCTUSB_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  octusb_interrupt_poll (struct octusb_softc*) ; 

__attribute__((used)) static void
octusb_do_poll(struct usb_bus *bus)
{
	struct octusb_softc *sc = OCTUSB_BUS2SC(bus);

	USB_BUS_LOCK(&sc->sc_bus);
	octusb_interrupt_poll(sc);
	USB_BUS_UNLOCK(&sc->sc_bus);
}