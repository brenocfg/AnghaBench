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
struct mwl_softc {scalar_t__ sc_tx_timer; int /*<<< orphan*/  sc_watchdog; scalar_t__ sc_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWL_LOCK_ASSERT (struct mwl_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwl_draintxq (struct mwl_softc*) ; 

__attribute__((used)) static void
mwl_stop(struct mwl_softc *sc)
{

	MWL_LOCK_ASSERT(sc);
	if (sc->sc_running) {
		/*
		 * Shutdown the hardware and driver.
		 */
		sc->sc_running = 0;
		callout_stop(&sc->sc_watchdog);
		sc->sc_tx_timer = 0;
		mwl_draintxq(sc);
	}
}