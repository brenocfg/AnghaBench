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
struct upgt_softc {int /*<<< orphan*/  sc_cur_rateset; } ;
struct ieee80211vap {struct ieee80211_txparam* iv_txparms; } ;
struct ieee80211com {scalar_t__ ic_curmode; int /*<<< orphan*/  ic_curchan; struct upgt_softc* ic_softc; } ;
struct ieee80211_txparam {size_t ucastrate; } ;

/* Variables and functions */
 size_t IEEE80211_FIXED_RATE_NONE ; 
 scalar_t__ IEEE80211_MODE_11B ; 
 scalar_t__ IEEE80211_MODE_11G ; 
 scalar_t__ IEEE80211_MODE_AUTO ; 
 size_t ieee80211_chan2mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int const,int) ; 

__attribute__((used)) static void
upgt_setup_rates(struct ieee80211vap *vap, struct ieee80211com *ic)
{
	struct upgt_softc *sc = ic->ic_softc;
	const struct ieee80211_txparam *tp;

	/*
	 * 0x01 = OFMD6   0x10 = DS1
	 * 0x04 = OFDM9   0x11 = DS2
	 * 0x06 = OFDM12  0x12 = DS5
	 * 0x07 = OFDM18  0x13 = DS11
	 * 0x08 = OFDM24
	 * 0x09 = OFDM36
	 * 0x0a = OFDM48
	 * 0x0b = OFDM54
	 */
	const uint8_t rateset_auto_11b[] =
	    { 0x13, 0x13, 0x12, 0x11, 0x11, 0x10, 0x10, 0x10 };
	const uint8_t rateset_auto_11g[] =
	    { 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x04, 0x01 };
	const uint8_t rateset_fix_11bg[] =
	    { 0x10, 0x11, 0x12, 0x13, 0x01, 0x04, 0x06, 0x07,
	      0x08, 0x09, 0x0a, 0x0b };

	tp = &vap->iv_txparms[ieee80211_chan2mode(ic->ic_curchan)];

	/* XXX */
	if (tp->ucastrate == IEEE80211_FIXED_RATE_NONE) {
		/*
		 * Automatic rate control is done by the device.
		 * We just pass the rateset from which the device
		 * will pickup a rate.
		 */
		if (ic->ic_curmode == IEEE80211_MODE_11B)
			memcpy(sc->sc_cur_rateset, rateset_auto_11b,
			    sizeof(sc->sc_cur_rateset));
		if (ic->ic_curmode == IEEE80211_MODE_11G ||
		    ic->ic_curmode == IEEE80211_MODE_AUTO)
			memcpy(sc->sc_cur_rateset, rateset_auto_11g,
			    sizeof(sc->sc_cur_rateset));
	} else {
		/* set a fixed rate */
		memset(sc->sc_cur_rateset, rateset_fix_11bg[tp->ucastrate],
		    sizeof(sc->sc_cur_rateset));
	}
}