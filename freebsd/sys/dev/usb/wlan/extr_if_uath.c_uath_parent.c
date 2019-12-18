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
struct uath_softc {int sc_flags; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct uath_softc* ic_softc; } ;

/* Variables and functions */
 int UATH_FLAG_INITDONE ; 
 int UATH_FLAG_INVALID ; 
 int /*<<< orphan*/  UATH_LOCK (struct uath_softc*) ; 
 int /*<<< orphan*/  UATH_UNLOCK (struct uath_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  uath_init (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_stop (struct uath_softc*) ; 

__attribute__((used)) static void
uath_parent(struct ieee80211com *ic)
{
	struct uath_softc *sc = ic->ic_softc;
	int startall = 0;

	UATH_LOCK(sc);
	if (sc->sc_flags & UATH_FLAG_INVALID) {
		UATH_UNLOCK(sc);
		return;
	}

	if (ic->ic_nrunning > 0) {
		if (!(sc->sc_flags & UATH_FLAG_INITDONE)) {
			uath_init(sc);
			startall = 1;
		}
	} else if (sc->sc_flags & UATH_FLAG_INITDONE)
		uath_stop(sc);
	UATH_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}