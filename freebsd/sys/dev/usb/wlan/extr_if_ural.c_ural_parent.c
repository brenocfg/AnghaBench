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
struct ural_softc {scalar_t__ sc_running; scalar_t__ sc_detached; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct ural_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  ural_init (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_setpromisc (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_stop (struct ural_softc*) ; 

__attribute__((used)) static void
ural_parent(struct ieee80211com *ic)
{
	struct ural_softc *sc = ic->ic_softc;
	int startall = 0;

	RAL_LOCK(sc);
	if (sc->sc_detached) {
		RAL_UNLOCK(sc);
		return;
	}
	if (ic->ic_nrunning > 0) {
		if (sc->sc_running == 0) {
			ural_init(sc);
			startall = 1;
		} else
			ural_setpromisc(sc);
	} else if (sc->sc_running)
		ural_stop(sc);
	RAL_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}