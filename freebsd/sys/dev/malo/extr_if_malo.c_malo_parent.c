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
struct malo_softc {scalar_t__ malo_running; int /*<<< orphan*/  malo_invalid; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct malo_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALO_LOCK (struct malo_softc*) ; 
 int /*<<< orphan*/  MALO_UNLOCK (struct malo_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  malo_init (struct malo_softc*) ; 
 int /*<<< orphan*/  malo_mode_init (struct malo_softc*) ; 
 int /*<<< orphan*/  malo_stop (struct malo_softc*) ; 

__attribute__((used)) static void
malo_parent(struct ieee80211com *ic)
{
	struct malo_softc *sc = ic->ic_softc;
	int startall = 0;

	MALO_LOCK(sc);
	if (ic->ic_nrunning > 0) {
		/*
		 * Beware of being called during attach/detach
		 * to reset promiscuous mode.  In that case we
		 * will still be marked UP but not RUNNING.
		 * However trying to re-init the interface
		 * is the wrong thing to do as we've already
		 * torn down much of our state.  There's
		 * probably a better way to deal with this.
		 */
		if (!sc->malo_running && !sc->malo_invalid) {
			malo_init(sc);
			startall = 1;
		}
		/*
		 * To avoid rescanning another access point,
		 * do not call malo_init() here.  Instead,
		 * only reflect promisc mode settings.
		 */
		malo_mode_init(sc);
	} else if (sc->malo_running)
		malo_stop(sc);
	MALO_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}