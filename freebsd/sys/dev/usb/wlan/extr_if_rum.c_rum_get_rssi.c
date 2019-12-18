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
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;
struct rum_softc {int /*<<< orphan*/  ext_5ghz_lna; scalar_t__ rssi_5ghz_corr; scalar_t__ rssi_2ghz_corr; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int RT2573_NOISE_FLOOR ; 

__attribute__((used)) static int
rum_get_rssi(struct rum_softc *sc, uint8_t raw)
{
	struct ieee80211com *ic = &sc->sc_ic;
	int lna, agc, rssi;

	lna = (raw >> 5) & 0x3;
	agc = raw & 0x1f;

	if (lna == 0) {
		/*
		 * No RSSI mapping
		 *
		 * NB: Since RSSI is relative to noise floor, -1 is
		 *     adequate for caller to know error happened.
		 */
		return -1;
	}

	rssi = (2 * agc) - RT2573_NOISE_FLOOR;

	if (IEEE80211_IS_CHAN_2GHZ(ic->ic_curchan)) {
		rssi += sc->rssi_2ghz_corr;

		if (lna == 1)
			rssi -= 64;
		else if (lna == 2)
			rssi -= 74;
		else if (lna == 3)
			rssi -= 90;
	} else {
		rssi += sc->rssi_5ghz_corr;

		if (!sc->ext_5ghz_lna && lna != 1)
			rssi += 4;

		if (lna == 1)
			rssi -= 64;
		else if (lna == 2)
			rssi -= 86;
		else if (lna == 3)
			rssi -= 100;
	}
	return rssi;
}