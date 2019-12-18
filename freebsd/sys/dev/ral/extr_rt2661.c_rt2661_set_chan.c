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
typedef  scalar_t__ u_int ;
struct ieee80211com {int dummy; } ;
struct rt2661_softc {int* txpow; int rffreq; scalar_t__ rf_rev; struct ieee80211_channel* sc_curchan; int /*<<< orphan*/  rfprog; struct ieee80211com sc_ic; } ;
struct rfprog {scalar_t__ chan; int r1; int r2; int r3; int r4; } ;
struct ieee80211_channel {scalar_t__ ic_flags; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ IEEE80211_CHAN_ANY ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RAL_RF1 ; 
 int /*<<< orphan*/  RAL_RF2 ; 
 int /*<<< orphan*/  RAL_RF3 ; 
 int /*<<< orphan*/  RAL_RF4 ; 
 int RT2661_BBPR94_DEFAULT ; 
 scalar_t__ RT2661_RF_2529 ; 
 scalar_t__ RT2661_RF_5325 ; 
 int RT2661_SMART_MODE ; 
 scalar_t__ ieee80211_chan2ieee (struct ieee80211com*,struct ieee80211_channel*) ; 
 int rt2661_bbp_read (struct rt2661_softc*,int) ; 
 int /*<<< orphan*/  rt2661_bbp_write (struct rt2661_softc*,int,int) ; 
 struct rfprog* rt2661_rf5225_1 ; 
 struct rfprog* rt2661_rf5225_2 ; 
 int /*<<< orphan*/  rt2661_rf_write (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2661_select_antenna (struct rt2661_softc*) ; 
 int /*<<< orphan*/  rt2661_select_band (struct rt2661_softc*,struct ieee80211_channel*) ; 

__attribute__((used)) static void
rt2661_set_chan(struct rt2661_softc *sc, struct ieee80211_channel *c)
{
	struct ieee80211com *ic = &sc->sc_ic;
	const struct rfprog *rfprog;
	uint8_t bbp3, bbp94 = RT2661_BBPR94_DEFAULT;
	int8_t power;
	u_int i, chan;

	chan = ieee80211_chan2ieee(ic, c);
	KASSERT(chan != 0 && chan != IEEE80211_CHAN_ANY, ("chan 0x%x", chan));

	/* select the appropriate RF settings based on what EEPROM says */
	rfprog = (sc->rfprog == 0) ? rt2661_rf5225_1 : rt2661_rf5225_2;

	/* find the settings for this channel (we know it exists) */
	for (i = 0; rfprog[i].chan != chan; i++);

	power = sc->txpow[i];
	if (power < 0) {
		bbp94 += power;
		power = 0;
	} else if (power > 31) {
		bbp94 += power - 31;
		power = 31;
	}

	/*
	 * If we are switching from the 2GHz band to the 5GHz band or
	 * vice-versa, BBP registers need to be reprogrammed.
	 */
	if (c->ic_flags != sc->sc_curchan->ic_flags) {
		rt2661_select_band(sc, c);
		rt2661_select_antenna(sc);
	}
	sc->sc_curchan = c;

	rt2661_rf_write(sc, RAL_RF1, rfprog[i].r1);
	rt2661_rf_write(sc, RAL_RF2, rfprog[i].r2);
	rt2661_rf_write(sc, RAL_RF3, rfprog[i].r3 | power << 7);
	rt2661_rf_write(sc, RAL_RF4, rfprog[i].r4 | sc->rffreq << 10);

	DELAY(200);

	rt2661_rf_write(sc, RAL_RF1, rfprog[i].r1);
	rt2661_rf_write(sc, RAL_RF2, rfprog[i].r2);
	rt2661_rf_write(sc, RAL_RF3, rfprog[i].r3 | power << 7 | 1);
	rt2661_rf_write(sc, RAL_RF4, rfprog[i].r4 | sc->rffreq << 10);

	DELAY(200);

	rt2661_rf_write(sc, RAL_RF1, rfprog[i].r1);
	rt2661_rf_write(sc, RAL_RF2, rfprog[i].r2);
	rt2661_rf_write(sc, RAL_RF3, rfprog[i].r3 | power << 7);
	rt2661_rf_write(sc, RAL_RF4, rfprog[i].r4 | sc->rffreq << 10);

	/* enable smart mode for MIMO-capable RFs */
	bbp3 = rt2661_bbp_read(sc, 3);

	bbp3 &= ~RT2661_SMART_MODE;
	if (sc->rf_rev == RT2661_RF_5325 || sc->rf_rev == RT2661_RF_2529)
		bbp3 |= RT2661_SMART_MODE;

	rt2661_bbp_write(sc, 3, bbp3);

	if (bbp94 != RT2661_BBPR94_DEFAULT)
		rt2661_bbp_write(sc, 94, bbp94);

	/* 5GHz radio needs a 1ms delay here */
	if (IEEE80211_IS_CHAN_5GHZ(c))
		DELAY(1000);
}