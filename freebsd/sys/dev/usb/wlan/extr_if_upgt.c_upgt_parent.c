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
struct upgt_softc {int sc_flags; } ;
struct ieee80211com {scalar_t__ ic_nrunning; scalar_t__ ic_allmulti; scalar_t__ ic_promisc; struct upgt_softc* ic_softc; } ;

/* Variables and functions */
 int UPGT_FLAG_DETACHED ; 
 int UPGT_FLAG_INITDONE ; 
 int /*<<< orphan*/  UPGT_LOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  UPGT_UNLOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  upgt_init (struct upgt_softc*) ; 
 int /*<<< orphan*/  upgt_set_multi (struct upgt_softc*) ; 
 int /*<<< orphan*/  upgt_stop (struct upgt_softc*) ; 

__attribute__((used)) static void
upgt_parent(struct ieee80211com *ic)
{
	struct upgt_softc *sc = ic->ic_softc;
	int startall = 0;

	UPGT_LOCK(sc);
	if (sc->sc_flags & UPGT_FLAG_DETACHED) {
		UPGT_UNLOCK(sc);
		return;
	}
	if (ic->ic_nrunning > 0) {
		if (sc->sc_flags & UPGT_FLAG_INITDONE) {
			if (ic->ic_allmulti > 0 || ic->ic_promisc > 0)
				upgt_set_multi(sc);
		} else {
			upgt_init(sc);
			startall = 1;
		}
	} else if (sc->sc_flags & UPGT_FLAG_INITDONE)
		upgt_stop(sc);
	UPGT_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}