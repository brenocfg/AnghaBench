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
typedef  int uint8_t ;
struct TYPE_2__ {int change_connect; scalar_t__ change_suspend; scalar_t__ status_suspend; scalar_t__ status_bus_reset; scalar_t__ status_vbus; scalar_t__ port_powered; } ;
struct avr32dci_softc {int /*<<< orphan*/  sc_bus; TYPE_1__ sc_flags; int /*<<< orphan*/  (* sc_clocks_on ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_EPTCTLDIS (int) ; 
 int AVR32_EPTCTL_EPT_ENABL ; 
 int /*<<< orphan*/  AVR32_EPTRST ; 
 int AVR32_EP_MAX ; 
 int /*<<< orphan*/  AVR32_WRITE_4 (struct avr32dci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avr32dci_clocks_off (struct avr32dci_softc*) ; 
 int /*<<< orphan*/  avr32dci_mod_ien (struct avr32dci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avr32dci_pull_down (struct avr32dci_softc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
avr32dci_uninit(struct avr32dci_softc *sc)
{
	uint8_t n;

	USB_BUS_LOCK(&sc->sc_bus);

	/* turn on clocks */
	(sc->sc_clocks_on) (&sc->sc_bus);

	/* disable interrupts */
	avr32dci_mod_ien(sc, 0, 0xFFFFFFFF);

	/* reset all endpoints */
	AVR32_WRITE_4(sc, AVR32_EPTRST, (1 << AVR32_EP_MAX) - 1);

	/* disable all endpoints */
	for (n = 0; n != AVR32_EP_MAX; n++) {
		/* disable endpoint */
		AVR32_WRITE_4(sc, AVR32_EPTCTLDIS(n), AVR32_EPTCTL_EPT_ENABL);
	}

	sc->sc_flags.port_powered = 0;
	sc->sc_flags.status_vbus = 0;
	sc->sc_flags.status_bus_reset = 0;
	sc->sc_flags.status_suspend = 0;
	sc->sc_flags.change_suspend = 0;
	sc->sc_flags.change_connect = 1;

	avr32dci_pull_down(sc);
	avr32dci_clocks_off(sc);

	USB_BUS_UNLOCK(&sc->sc_bus);
}