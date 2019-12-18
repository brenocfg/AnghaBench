#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int change_connect; scalar_t__ change_suspend; scalar_t__ status_suspend; scalar_t__ status_bus_reset; scalar_t__ status_vbus; scalar_t__ port_powered; scalar_t__ port_enabled; } ;
struct dwc_otg_softc {int /*<<< orphan*/  sc_timer; int /*<<< orphan*/  sc_bus; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCTL_SFTDISCON ; 
 int /*<<< orphan*/  DOTG_DCTL ; 
 int /*<<< orphan*/  DOTG_GAHBCFG ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_clocks_off (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_pull_down (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_timer_stop (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 

void
dwc_otg_uninit(struct dwc_otg_softc *sc)
{
	USB_BUS_LOCK(&sc->sc_bus);

	/* stop host timer */
	dwc_otg_timer_stop(sc);

	/* set disconnect */
	DWC_OTG_WRITE_4(sc, DOTG_DCTL,
	    DCTL_SFTDISCON);

	/* turn off global IRQ */
	DWC_OTG_WRITE_4(sc, DOTG_GAHBCFG, 0);

	sc->sc_flags.port_enabled = 0;
	sc->sc_flags.port_powered = 0;
	sc->sc_flags.status_vbus = 0;
	sc->sc_flags.status_bus_reset = 0;
	sc->sc_flags.status_suspend = 0;
	sc->sc_flags.change_suspend = 0;
	sc->sc_flags.change_connect = 1;

	dwc_otg_pull_down(sc);
	dwc_otg_clocks_off(sc);

	USB_BUS_UNLOCK(&sc->sc_bus);

	usb_callout_drain(&sc->sc_timer);
}