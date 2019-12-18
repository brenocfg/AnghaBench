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
struct rt2860_softc {int sc_flags; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct rt2860_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct rt2860_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct rt2860_softc*) ; 
 int RT2860_RUNNING ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  rt2860_init_locked (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_stop_locked (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_update_promisc (struct ieee80211com*) ; 

__attribute__((used)) static void
rt2860_parent(struct ieee80211com *ic)
{
	struct rt2860_softc *sc = ic->ic_softc;
	int startall = 0;

	RAL_LOCK(sc);
	if (ic->ic_nrunning> 0) {
		if (!(sc->sc_flags & RT2860_RUNNING)) {
			rt2860_init_locked(sc);
			startall = 1;
		} else
			rt2860_update_promisc(ic);
	} else if (sc->sc_flags & RT2860_RUNNING)
		rt2860_stop_locked(sc);
	RAL_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}