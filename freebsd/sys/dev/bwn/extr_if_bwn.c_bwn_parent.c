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
struct ieee80211com {scalar_t__ ic_nrunning; struct bwn_softc* ic_softc; } ;
struct bwn_softc {int sc_flags; } ;

/* Variables and functions */
 int BWN_FLAG_RUNNING ; 
 int /*<<< orphan*/  BWN_LOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_UNLOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  bwn_init (struct bwn_softc*) ; 
 int /*<<< orphan*/  bwn_stop (struct bwn_softc*) ; 
 int /*<<< orphan*/  bwn_update_promisc (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 

__attribute__((used)) static void
bwn_parent(struct ieee80211com *ic)
{
	struct bwn_softc *sc = ic->ic_softc;
	int startall = 0;

	BWN_LOCK(sc);
	if (ic->ic_nrunning > 0) {
		if ((sc->sc_flags & BWN_FLAG_RUNNING) == 0) {
			bwn_init(sc);
			startall = 1;
		} else
			bwn_update_promisc(ic);
	} else if (sc->sc_flags & BWN_FLAG_RUNNING)
		bwn_stop(sc);
	BWN_UNLOCK(sc);

	if (startall)
		ieee80211_start_all(ic);
}