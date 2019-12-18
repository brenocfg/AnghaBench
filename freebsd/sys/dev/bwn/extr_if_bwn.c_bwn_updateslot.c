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
struct ieee80211com {struct bwn_softc* ic_softc; } ;
struct bwn_softc {int sc_flags; scalar_t__ sc_curmac; } ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int BWN_FLAG_RUNNING ; 
 int /*<<< orphan*/  BWN_LOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_UNLOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  IEEE80211_GET_SLOTTIME (struct ieee80211com*) ; 
 int /*<<< orphan*/  bwn_set_slot_time (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_updateslot(struct ieee80211com *ic)
{
	struct bwn_softc *sc = ic->ic_softc;
	struct bwn_mac *mac;

	BWN_LOCK(sc);
	if (sc->sc_flags & BWN_FLAG_RUNNING) {
		mac = (struct bwn_mac *)sc->sc_curmac;
		bwn_set_slot_time(mac, IEEE80211_GET_SLOTTIME(ic));
	}
	BWN_UNLOCK(sc);
}