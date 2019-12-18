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
struct dwc_otg_softc {int /*<<< orphan*/  sc_timer; scalar_t__ sc_timer_active; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/  sc_tmr_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int DWC_OTG_HOST_TIMER_RATE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_enable_sof_irq (struct dwc_otg_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct dwc_otg_softc*) ; 

__attribute__((used)) static void
dwc_otg_timer(void *_sc)
{
	struct dwc_otg_softc *sc = _sc;

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	DPRINTF("\n");

	USB_BUS_SPIN_LOCK(&sc->sc_bus);

	/* increment timer value */
	sc->sc_tmr_val++;

	/* enable SOF interrupt, which will poll jobs */
	dwc_otg_enable_sof_irq(sc);

	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);

	if (sc->sc_timer_active) {
		/* restart timer */
		usb_callout_reset(&sc->sc_timer,
		    hz / (1000 / DWC_OTG_HOST_TIMER_RATE),
		    &dwc_otg_timer, sc);
	}
}