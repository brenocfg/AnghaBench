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
struct dwc_otg_softc {int sc_timer_active; int /*<<< orphan*/  sc_timer; } ;

/* Variables and functions */
 int DWC_OTG_HOST_TIMER_RATE ; 
 int /*<<< orphan*/  dwc_otg_timer ; 
 int hz ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct dwc_otg_softc*) ; 

__attribute__((used)) static void
dwc_otg_timer_start(struct dwc_otg_softc *sc)
{
	if (sc->sc_timer_active != 0)
		return;

	sc->sc_timer_active = 1;

	/* restart timer */
	usb_callout_reset(&sc->sc_timer,
	    hz / (1000 / DWC_OTG_HOST_TIMER_RATE),
	    &dwc_otg_timer, sc);
}