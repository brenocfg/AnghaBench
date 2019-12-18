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
struct musbotg_softc {int /*<<< orphan*/  sc_bus; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  musbotg_root_intr (struct musbotg_softc*) ; 

void
musbotg_vbus_interrupt(struct musbotg_softc *sc, uint8_t is_on)
{
	DPRINTFN(4, "vbus = %u\n", is_on);

	USB_BUS_LOCK(&sc->sc_bus);
	if (is_on) {
		if (!sc->sc_flags.status_vbus) {
			sc->sc_flags.status_vbus = 1;

			/* complete root HUB interrupt endpoint */
			musbotg_root_intr(sc);
		}
	} else {
		if (sc->sc_flags.status_vbus) {
			sc->sc_flags.status_vbus = 0;
			sc->sc_flags.status_bus_reset = 0;
			sc->sc_flags.status_suspend = 0;
			sc->sc_flags.change_suspend = 0;
			sc->sc_flags.change_connect = 1;

			/* complete root HUB interrupt endpoint */
			musbotg_root_intr(sc);
		}
	}

	USB_BUS_UNLOCK(&sc->sc_bus);
}