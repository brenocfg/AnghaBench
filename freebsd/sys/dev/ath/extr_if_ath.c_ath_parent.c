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
struct ieee80211com {scalar_t__ ic_nrunning; struct ath_softc* ic_softc; } ;
struct ath_softc {TYPE_1__* sc_tx99; int /*<<< orphan*/  sc_invalid; scalar_t__ sc_running; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int EDOOFUS ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  HAL_PM_FULL_SLEEP ; 
 int ath_init (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_mode_init (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_power_setpower (struct ath_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_stop (struct ath_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
ath_parent(struct ieee80211com *ic)
{
	struct ath_softc *sc = ic->ic_softc;
	int error = EDOOFUS;

	ATH_LOCK(sc);
	if (ic->ic_nrunning > 0) {
		/*
		 * To avoid rescanning another access point,
		 * do not call ath_init() here.  Instead,
		 * only reflect promisc mode settings.
		 */
		if (sc->sc_running) {
			ath_power_set_power_state(sc, HAL_PM_AWAKE);
			ath_mode_init(sc);
			ath_power_restore_power_state(sc);
		} else if (!sc->sc_invalid) {
			/*
			 * Beware of being called during attach/detach
			 * to reset promiscuous mode.  In that case we
			 * will still be marked UP but not RUNNING.
			 * However trying to re-init the interface
			 * is the wrong thing to do as we've already
			 * torn down much of our state.  There's
			 * probably a better way to deal with this.
			 */
			error = ath_init(sc);
		}
	} else {
		ath_stop(sc);
		if (!sc->sc_invalid)
			ath_power_setpower(sc, HAL_PM_FULL_SLEEP, 1);
	}
	ATH_UNLOCK(sc);

	if (error == 0) {                        
#ifdef ATH_TX99_DIAG
		if (sc->sc_tx99 != NULL)
			sc->sc_tx99->start(sc->sc_tx99);
		else
#endif
		ieee80211_start_all(ic);
	}
}