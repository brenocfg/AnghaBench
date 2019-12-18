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
struct dwc_otg_softc {int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 struct dwc_otg_softc* DWC_OTG_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_interrupt_complete_locked (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_interrupt_poll_locked (struct dwc_otg_softc*) ; 

__attribute__((used)) static void
dwc_otg_do_poll(struct usb_bus *bus)
{
	struct dwc_otg_softc *sc = DWC_OTG_BUS2SC(bus);

	USB_BUS_LOCK(&sc->sc_bus);
	USB_BUS_SPIN_LOCK(&sc->sc_bus);
	dwc_otg_interrupt_poll_locked(sc);
	dwc_otg_interrupt_complete_locked(sc);
	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
	USB_BUS_UNLOCK(&sc->sc_bus);
}