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
typedef  int uint32_t ;
struct TYPE_2__ {int status_bus_reset; int status_suspend; int change_suspend; int change_connect; } ;
struct avr32dci_softc {int /*<<< orphan*/  sc_bus; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_CLRINT ; 
 int /*<<< orphan*/  AVR32_INTSTA ; 
 int AVR32_INT_DET_SUSPD ; 
 int AVR32_INT_ENDRESET ; 
 int AVR32_INT_EPT_INT (int /*<<< orphan*/ ) ; 
 int AVR32_INT_WAKE_UP ; 
 int AVR32_READ_4 (struct avr32dci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVR32_WRITE_4 (struct avr32dci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avr32dci_interrupt_poll (struct avr32dci_softc*) ; 
 int /*<<< orphan*/  avr32dci_mod_ien (struct avr32dci_softc*,int,int) ; 
 int /*<<< orphan*/  avr32dci_root_intr (struct avr32dci_softc*) ; 

void
avr32dci_interrupt(struct avr32dci_softc *sc)
{
	uint32_t status;

	USB_BUS_LOCK(&sc->sc_bus);

	/* read interrupt status */
	status = AVR32_READ_4(sc, AVR32_INTSTA);

	/* clear all set interrupts */
	AVR32_WRITE_4(sc, AVR32_CLRINT, status);

	DPRINTFN(14, "INTSTA=0x%08x\n", status);

	/* check for any bus state change interrupts */
	if (status & AVR32_INT_ENDRESET) {

		DPRINTFN(5, "end of reset\n");

		/* set correct state */
		sc->sc_flags.status_bus_reset = 1;
		sc->sc_flags.status_suspend = 0;
		sc->sc_flags.change_suspend = 0;
		sc->sc_flags.change_connect = 1;

		/* disable resume interrupt */
		avr32dci_mod_ien(sc, AVR32_INT_DET_SUSPD |
		    AVR32_INT_ENDRESET, AVR32_INT_WAKE_UP);

		/* complete root HUB interrupt endpoint */
		avr32dci_root_intr(sc);
	}
	/*
	 * If resume and suspend is set at the same time we interpret
	 * that like RESUME. Resume is set when there is at least 3
	 * milliseconds of inactivity on the USB BUS.
	 */
	if (status & AVR32_INT_WAKE_UP) {

		DPRINTFN(5, "resume interrupt\n");

		if (sc->sc_flags.status_suspend) {
			/* update status bits */
			sc->sc_flags.status_suspend = 0;
			sc->sc_flags.change_suspend = 1;

			/* disable resume interrupt */
			avr32dci_mod_ien(sc, AVR32_INT_DET_SUSPD |
			    AVR32_INT_ENDRESET, AVR32_INT_WAKE_UP);

			/* complete root HUB interrupt endpoint */
			avr32dci_root_intr(sc);
		}
	} else if (status & AVR32_INT_DET_SUSPD) {

		DPRINTFN(5, "suspend interrupt\n");

		if (!sc->sc_flags.status_suspend) {
			/* update status bits */
			sc->sc_flags.status_suspend = 1;
			sc->sc_flags.change_suspend = 1;

			/* disable suspend interrupt */
			avr32dci_mod_ien(sc, AVR32_INT_WAKE_UP |
			    AVR32_INT_ENDRESET, AVR32_INT_DET_SUSPD);

			/* complete root HUB interrupt endpoint */
			avr32dci_root_intr(sc);
		}
	}
	/* check for any endpoint interrupts */
	if (status & -AVR32_INT_EPT_INT(0)) {

		DPRINTFN(5, "real endpoint interrupt\n");

		avr32dci_interrupt_poll(sc);
	}
	USB_BUS_UNLOCK(&sc->sc_bus);
}