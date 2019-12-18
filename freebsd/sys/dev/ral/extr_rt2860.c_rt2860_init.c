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
struct ieee80211com {int dummy; } ;
struct rt2860_softc {int sc_flags; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct rt2860_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct rt2860_softc*) ; 
 int RT2860_RUNNING ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  rt2860_init_locked (struct rt2860_softc*) ; 

__attribute__((used)) static void
rt2860_init(void *arg)
{
	struct rt2860_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;

	RAL_LOCK(sc);
	rt2860_init_locked(sc);
	RAL_UNLOCK(sc);

	if (sc->sc_flags & RT2860_RUNNING)
		ieee80211_start_all(ic);
}