#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_bus {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_1__ ehci_softc_t ;

/* Variables and functions */
 TYPE_1__* EHCI_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_interrupt_poll (TYPE_1__*) ; 

__attribute__((used)) static void
ehci_do_poll(struct usb_bus *bus)
{
	ehci_softc_t *sc = EHCI_BUS2SC(bus);

	USB_BUS_LOCK(&sc->sc_bus);
	ehci_interrupt_poll(sc);
	USB_BUS_UNLOCK(&sc->sc_bus);
}