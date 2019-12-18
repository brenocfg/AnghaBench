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
struct TYPE_2__ {int change_connect; scalar_t__ change_suspend; scalar_t__ status_suspend; scalar_t__ status_bus_reset; scalar_t__ status_vbus; scalar_t__ port_powered; } ;
struct atmegadci_softc {int /*<<< orphan*/  sc_bus; TYPE_1__ sc_flags; int /*<<< orphan*/  (* sc_clocks_on ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ATMEGA_EP_MAX ; 
 int /*<<< orphan*/  ATMEGA_UDIEN ; 
 int /*<<< orphan*/  ATMEGA_UERST ; 
 int /*<<< orphan*/  ATMEGA_UHWCON ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atmegadci_clocks_off (struct atmegadci_softc*) ; 
 int /*<<< orphan*/  atmegadci_pull_down (struct atmegadci_softc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
atmegadci_uninit(struct atmegadci_softc *sc)
{
	USB_BUS_LOCK(&sc->sc_bus);

	/* turn on clocks */
	(sc->sc_clocks_on) (&sc->sc_bus);

	/* disable interrupts */
	ATMEGA_WRITE_1(sc, ATMEGA_UDIEN, 0);

	/* reset all endpoints */
	ATMEGA_WRITE_1(sc, ATMEGA_UERST,
	    (1 << ATMEGA_EP_MAX) - 1);

	/* disable reset */
	ATMEGA_WRITE_1(sc, ATMEGA_UERST, 0);

	sc->sc_flags.port_powered = 0;
	sc->sc_flags.status_vbus = 0;
	sc->sc_flags.status_bus_reset = 0;
	sc->sc_flags.status_suspend = 0;
	sc->sc_flags.change_suspend = 0;
	sc->sc_flags.change_connect = 1;

	atmegadci_pull_down(sc);
	atmegadci_clocks_off(sc);

	/* disable USB PAD regulator */
	ATMEGA_WRITE_1(sc, ATMEGA_UHWCON, 0);

	USB_BUS_UNLOCK(&sc->sc_bus);
}