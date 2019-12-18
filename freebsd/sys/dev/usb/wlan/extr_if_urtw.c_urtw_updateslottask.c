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
struct ieee80211com {int ic_flags; int /*<<< orphan*/  ic_curchan; } ;
struct urtw_softc {int sc_flags; scalar_t__ sc_state; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int IEEE80211_DUR_SHSLOT ; 
 int IEEE80211_DUR_SLOT ; 
 int IEEE80211_F_SHSLOT ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_S_ASSOC ; 
 int /*<<< orphan*/  URTW_8187B_EIFS ; 
 int /*<<< orphan*/  URTW_CARRIER_SCOUNT ; 
 int /*<<< orphan*/  URTW_CW_VAL ; 
 int /*<<< orphan*/  URTW_DIFS ; 
 int /*<<< orphan*/  URTW_EIFS ; 
 int /*<<< orphan*/  URTW_LOCK (struct urtw_softc*) ; 
 int URTW_RTL8187B ; 
 int URTW_RUNNING ; 
 int /*<<< orphan*/  URTW_SIFS ; 
 int /*<<< orphan*/  URTW_SLOT ; 
 int /*<<< orphan*/  URTW_UNLOCK (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
urtw_updateslottask(void *arg, int pending)
{
	struct urtw_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;
	int error;

	URTW_LOCK(sc);
	if ((sc->sc_flags & URTW_RUNNING) == 0) {
		URTW_UNLOCK(sc);
		return;
	}
	if (sc->sc_flags & URTW_RTL8187B) {
		urtw_write8_m(sc, URTW_SIFS, 0x22);
		if (IEEE80211_IS_CHAN_ANYG(ic->ic_curchan))
			urtw_write8_m(sc, URTW_SLOT, IEEE80211_DUR_SHSLOT);
		else
			urtw_write8_m(sc, URTW_SLOT, IEEE80211_DUR_SLOT);
		urtw_write8_m(sc, URTW_8187B_EIFS, 0x5b);
		urtw_write8_m(sc, URTW_CARRIER_SCOUNT, 0x5b);
	} else {
		urtw_write8_m(sc, URTW_SIFS, 0x22);
		if (sc->sc_state == IEEE80211_S_ASSOC &&
		    ic->ic_flags & IEEE80211_F_SHSLOT)
			urtw_write8_m(sc, URTW_SLOT, IEEE80211_DUR_SHSLOT);
		else
			urtw_write8_m(sc, URTW_SLOT, IEEE80211_DUR_SLOT);
		if (IEEE80211_IS_CHAN_ANYG(ic->ic_curchan)) {
			urtw_write8_m(sc, URTW_DIFS, 0x14);
			urtw_write8_m(sc, URTW_EIFS, 0x5b - 0x14);
			urtw_write8_m(sc, URTW_CW_VAL, 0x73);
		} else {
			urtw_write8_m(sc, URTW_DIFS, 0x24);
			urtw_write8_m(sc, URTW_EIFS, 0x5b - 0x24);
			urtw_write8_m(sc, URTW_CW_VAL, 0xa5);
		}
	}
fail:
	URTW_UNLOCK(sc);
}