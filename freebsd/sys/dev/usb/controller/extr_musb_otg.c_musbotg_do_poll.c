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
struct musbotg_softc {int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 struct musbotg_softc* MUSBOTG_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  musbotg_interrupt_poll (struct musbotg_softc*) ; 

__attribute__((used)) static void
musbotg_do_poll(struct usb_bus *bus)
{
	struct musbotg_softc *sc = MUSBOTG_BUS2SC(bus);

	USB_BUS_LOCK(&sc->sc_bus);
	musbotg_interrupt_poll(sc);
	USB_BUS_UNLOCK(&sc->sc_bus);
}