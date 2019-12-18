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
struct ath_softc {int /*<<< orphan*/ * sc_rxlink; int /*<<< orphan*/  sc_invalid; scalar_t__ sc_blinking; int /*<<< orphan*/  sc_ledon; int /*<<< orphan*/  sc_ledpin; int /*<<< orphan*/  sc_ledtimer; scalar_t__ sc_softled; scalar_t__ sc_running; scalar_t__ sc_wd_timer; int /*<<< orphan*/  sc_wd_ch; TYPE_1__* sc_tx99; struct ath_hal* sc_ah; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_LOCK_ASSERT (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_RESET_DEFAULT ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  ath_beacon_free (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_draintxq (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_gpioset (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_intrset (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_phydisable (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_stoprecv (struct ath_softc*,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
ath_stop(struct ath_softc *sc)
{
	struct ath_hal *ah = sc->sc_ah;

	ATH_LOCK_ASSERT(sc);

	/*
	 * Wake the hardware up before fiddling with it.
	 */
	ath_power_set_power_state(sc, HAL_PM_AWAKE);

	if (sc->sc_running) {
		/*
		 * Shutdown the hardware and driver:
		 *    reset 802.11 state machine
		 *    turn off timers
		 *    disable interrupts
		 *    turn off the radio
		 *    clear transmit machinery
		 *    clear receive machinery
		 *    drain and release tx queues
		 *    reclaim beacon resources
		 *    power down hardware
		 *
		 * Note that some of this work is not possible if the
		 * hardware is gone (invalid).
		 */
#ifdef ATH_TX99_DIAG
		if (sc->sc_tx99 != NULL)
			sc->sc_tx99->stop(sc->sc_tx99);
#endif
		callout_stop(&sc->sc_wd_ch);
		sc->sc_wd_timer = 0;
		sc->sc_running = 0;
		if (!sc->sc_invalid) {
			if (sc->sc_softled) {
				callout_stop(&sc->sc_ledtimer);
				ath_hal_gpioset(ah, sc->sc_ledpin,
					!sc->sc_ledon);
				sc->sc_blinking = 0;
			}
			ath_hal_intrset(ah, 0);
		}
		/* XXX we should stop RX regardless of whether it's valid */
		if (!sc->sc_invalid) {
			ath_stoprecv(sc, 1);
			ath_hal_phydisable(ah);
		} else
			sc->sc_rxlink = NULL;
		ath_draintxq(sc, ATH_RESET_DEFAULT);
		ath_beacon_free(sc);	/* XXX not needed */
	}

	/* And now, restore the current power state */
	ath_power_restore_power_state(sc);
}