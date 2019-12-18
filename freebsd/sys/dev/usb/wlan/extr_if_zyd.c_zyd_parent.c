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
struct zyd_softc {int sc_flags; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct zyd_softc* ic_softc; } ;

/* Variables and functions */
 int ZYD_FLAG_DETACHED ; 
 int ZYD_FLAG_RUNNING ; 
 int /*<<< orphan*/  ZYD_LOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  ZYD_UNLOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  zyd_init_locked (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_set_multi (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_stop (struct zyd_softc*) ; 

__attribute__((used)) static void
zyd_parent(struct ieee80211com *ic)
{
	struct zyd_softc *sc = ic->ic_softc;
	int startall = 0;

	ZYD_LOCK(sc);
	if (sc->sc_flags & ZYD_FLAG_DETACHED) {
		ZYD_UNLOCK(sc);
		return;
	}
	if (ic->ic_nrunning > 0) {
		if ((sc->sc_flags & ZYD_FLAG_RUNNING) == 0) {
			zyd_init_locked(sc);
			startall = 1;
		} else
			zyd_set_multi(sc);
	} else if (sc->sc_flags & ZYD_FLAG_RUNNING)
		zyd_stop(sc);
	ZYD_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}