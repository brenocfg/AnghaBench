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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct ieee80211com {int dummy; } ;
struct rtwn_softc {int sc_flags; struct r12a_softc* sc_priv; struct ieee80211com sc_ic; } ;
struct r12a_softc {int tx_bbswing_2g; int tx_bbswing_5g; } ;
struct ieee80211_channel {int /*<<< orphan*/  ic_flags; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel*) ; 
 int IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  R12A_CCK_CHECK ; 
 int R12A_CCK_CHECK_5GHZ ; 
 int /*<<< orphan*/  R12A_TX_SCALE (int) ; 
 int /*<<< orphan*/  R12A_TX_SCALE_SWING_M ; 
 int R12A_TX_SCALE_SWING_S ; 
 int RTWN_RUNNING ; 
 int RTWN_STARTED ; 
 int /*<<< orphan*/  ieee80211_get_suprates (struct ieee80211com*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_get_rates (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtwn_r12a_set_band_2ghz (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_r12a_set_band_5ghz (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int rtwn_read_1 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r12a_set_band(struct rtwn_softc *sc, struct ieee80211_channel *c)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct r12a_softc *rs = sc->sc_priv;
	uint32_t basicrates;
	uint8_t swing;
	int i;

	/* Check if band was changed. */
	if ((sc->sc_flags & (RTWN_STARTED | RTWN_RUNNING)) !=
	    RTWN_STARTED && IEEE80211_IS_CHAN_5GHZ(c) ^
	    !(rtwn_read_1(sc, R12A_CCK_CHECK) & R12A_CCK_CHECK_5GHZ))
		return;

	rtwn_get_rates(sc, ieee80211_get_suprates(ic, c), NULL, &basicrates,
	    NULL, 1);
	if (IEEE80211_IS_CHAN_2GHZ(c)) {
		rtwn_r12a_set_band_2ghz(sc, basicrates);
		swing = rs->tx_bbswing_2g;
	} else if (IEEE80211_IS_CHAN_5GHZ(c)) {
		rtwn_r12a_set_band_5ghz(sc, basicrates);
		swing = rs->tx_bbswing_5g;
	} else {
		KASSERT(0, ("wrong channel flags %08X\n", c->ic_flags));
		return;
	}

	/* XXX PATH_B is set by vendor driver. */
	for (i = 0; i < 2; i++) {
		uint16_t val = 0;

		switch ((swing >> i * 2) & 0x3) {
		case 0:
			val = 0x200;	/* 0 dB	*/
			break;
		case 1:
			val = 0x16a;	/* -3 dB */
			break;
		case 2:
			val = 0x101;	/* -6 dB */
			break;
		case 3:
			val = 0xb6;	/* -9 dB */
			break;
		}

		rtwn_bb_setbits(sc, R12A_TX_SCALE(i), R12A_TX_SCALE_SWING_M,
		    val << R12A_TX_SCALE_SWING_S);
	}
}