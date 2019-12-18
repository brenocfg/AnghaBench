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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int status_vbus; int change_connect; scalar_t__ change_suspend; scalar_t__ status_suspend; scalar_t__ status_bus_reset; } ;
struct dwc_otg_softc {scalar_t__ sc_mode; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,scalar_t__) ; 
 scalar_t__ DWC_MODE_HOST ; 
 int /*<<< orphan*/  dwc_otg_root_intr (struct dwc_otg_softc*) ; 

__attribute__((used)) static void
dwc_otg_vbus_interrupt(struct dwc_otg_softc *sc, uint8_t is_on)
{
	DPRINTFN(5, "vbus = %u\n", is_on);

	/*
	 * If the USB host mode is forced, then assume VBUS is always
	 * present else rely on the input to this function:
	 */
	if ((is_on != 0) || (sc->sc_mode == DWC_MODE_HOST)) {

		if (!sc->sc_flags.status_vbus) {
			sc->sc_flags.status_vbus = 1;

			/* complete root HUB interrupt endpoint */

			dwc_otg_root_intr(sc);
		}
	} else {
		if (sc->sc_flags.status_vbus) {
			sc->sc_flags.status_vbus = 0;
			sc->sc_flags.status_bus_reset = 0;
			sc->sc_flags.status_suspend = 0;
			sc->sc_flags.change_suspend = 0;
			sc->sc_flags.change_connect = 1;

			/* complete root HUB interrupt endpoint */

			dwc_otg_root_intr(sc);
		}
	}
}