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
typedef  int /*<<< orphan*/  uint8_t ;
struct ukbd_softc {int sc_flags; scalar_t__ sc_inputs; int sc_time_ms; int /*<<< orphan*/  sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PRI_UNCHANGED ; 
 int UKBD_FLAG_POLLING ; 
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 int /*<<< orphan*/  UKBD_N_TRANSFER ; 
 scalar_t__ USB_IN_POLLING_MODE_FUNC () ; 
 int /*<<< orphan*/  kern_yield (int /*<<< orphan*/ ) ; 
 scalar_t__ ukbd_any_key_pressed (struct ukbd_softc*) ; 
 int /*<<< orphan*/  ukbd_interrupt (struct ukbd_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ukbd_do_poll(struct ukbd_softc *sc, uint8_t wait)
{

	UKBD_LOCK_ASSERT();
	KASSERT((sc->sc_flags & UKBD_FLAG_POLLING) != 0,
	    ("ukbd_do_poll called when not polling\n"));
	DPRINTFN(2, "polling\n");

	if (USB_IN_POLLING_MODE_FUNC() == 0) {
		/*
		 * In this context the kernel is polling for input,
		 * but the USB subsystem works in normal interrupt-driven
		 * mode, so we just wait on the USB threads to do the job.
		 * Note that we currently hold the Giant, but it's also used
		 * as the transfer mtx, so we must release it while waiting.
		 */
		while (sc->sc_inputs == 0) {
			/*
			 * Give USB threads a chance to run.  Note that
			 * kern_yield performs DROP_GIANT + PICKUP_GIANT.
			 */
			kern_yield(PRI_UNCHANGED);
			if (!wait)
				break;
		}
		return;
	}

	while (sc->sc_inputs == 0) {

		usbd_transfer_poll(sc->sc_xfer, UKBD_N_TRANSFER);

		/* Delay-optimised support for repetition of keys */
		if (ukbd_any_key_pressed(sc)) {
			/* a key is pressed - need timekeeping */
			DELAY(1000);

			/* 1 millisecond has passed */
			sc->sc_time_ms += 1;
		}

		ukbd_interrupt(sc);

		if (!wait)
			break;
	}
}