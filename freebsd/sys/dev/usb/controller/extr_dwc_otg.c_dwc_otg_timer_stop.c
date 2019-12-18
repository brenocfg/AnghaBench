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
struct dwc_otg_softc {scalar_t__ sc_timer_active; int /*<<< orphan*/  sc_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dwc_otg_timer_stop(struct dwc_otg_softc *sc)
{
	if (sc->sc_timer_active == 0)
		return;

	sc->sc_timer_active = 0;

	/* stop timer */
	usb_callout_stop(&sc->sc_timer);
}