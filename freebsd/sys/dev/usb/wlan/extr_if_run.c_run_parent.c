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
struct run_softc {int sc_flags; int rvp_cnt; scalar_t__ sc_detached; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct run_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int RUN_RUNNING ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  run_init_locked (struct run_softc*) ; 
 int /*<<< orphan*/  run_stop (struct run_softc*) ; 
 int /*<<< orphan*/  run_update_promisc_locked (struct run_softc*) ; 

__attribute__((used)) static void
run_parent(struct ieee80211com *ic)
{
	struct run_softc *sc = ic->ic_softc;
	int startall = 0;

	RUN_LOCK(sc);
	if (sc->sc_detached) {
		RUN_UNLOCK(sc);
		return;
	}

	if (ic->ic_nrunning > 0) {
		if (!(sc->sc_flags & RUN_RUNNING)) {
			startall = 1;
			run_init_locked(sc);
		} else
			run_update_promisc_locked(sc);
	} else if ((sc->sc_flags & RUN_RUNNING) && sc->rvp_cnt <= 1)
		run_stop(sc);
	RUN_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}