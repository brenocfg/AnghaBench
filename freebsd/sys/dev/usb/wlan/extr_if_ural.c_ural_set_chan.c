#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ieee80211com {int ic_txpowlimit; scalar_t__ ic_opmode; int ic_flags; } ;
struct ural_softc {int rf_rev; int /*<<< orphan*/ * txpow; struct ieee80211com sc_ic; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_2__ {int chan; int r1; int r2; int r4; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int) ; 
 int IEEE80211_CHAN_ANY ; 
 int IEEE80211_F_SCAN ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_M_MONITOR ; 
 int RAL_JAPAN_FILTER ; 
 int /*<<< orphan*/  RAL_RF1 ; 
 int /*<<< orphan*/  RAL_RF2 ; 
 int /*<<< orphan*/  RAL_RF3 ; 
 int /*<<< orphan*/  RAL_RF4 ; 
#define  RAL_RF_2522 134 
#define  RAL_RF_2523 133 
#define  RAL_RF_2524 132 
#define  RAL_RF_2525 131 
#define  RAL_RF_2525E 130 
#define  RAL_RF_2526 129 
#define  RAL_RF_5222 128 
 int /*<<< orphan*/  RAL_STA_CSR0 ; 
 int hz ; 
 int ieee80211_chan2ieee (struct ieee80211com*,struct ieee80211_channel*) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int ural_bbp_read (struct ural_softc*,int) ; 
 int /*<<< orphan*/  ural_bbp_write (struct ural_softc*,int,int) ; 
 int /*<<< orphan*/  ural_disable_rf_tune (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_pause (struct ural_softc*,int) ; 
 int /*<<< orphan*/  ural_read (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int* ural_rf2522_r2 ; 
 int* ural_rf2523_r2 ; 
 int* ural_rf2524_r2 ; 
 int* ural_rf2525_hi_r2 ; 
 int* ural_rf2525_r2 ; 
 int* ural_rf2525e_r2 ; 
 int* ural_rf2526_hi_r2 ; 
 int* ural_rf2526_r2 ; 
 TYPE_1__* ural_rf5222 ; 
 int /*<<< orphan*/  ural_rf_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ural_set_basicrates (struct ural_softc*,struct ieee80211_channel*) ; 

__attribute__((used)) static void
ural_set_chan(struct ural_softc *sc, struct ieee80211_channel *c)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint8_t power, tmp;
	int i, chan;

	chan = ieee80211_chan2ieee(ic, c);
	if (chan == 0 || chan == IEEE80211_CHAN_ANY)
		return;

	if (IEEE80211_IS_CHAN_2GHZ(c))
		power = min(sc->txpow[chan - 1], 31);
	else
		power = 31;

	/* adjust txpower using ifconfig settings */
	power -= (100 - ic->ic_txpowlimit) / 8;

	DPRINTFN(2, "setting channel to %u, txpower to %u\n", chan, power);

	switch (sc->rf_rev) {
	case RAL_RF_2522:
		ural_rf_write(sc, RAL_RF1, 0x00814);
		ural_rf_write(sc, RAL_RF2, ural_rf2522_r2[chan - 1]);
		ural_rf_write(sc, RAL_RF3, power << 7 | 0x00040);
		break;

	case RAL_RF_2523:
		ural_rf_write(sc, RAL_RF1, 0x08804);
		ural_rf_write(sc, RAL_RF2, ural_rf2523_r2[chan - 1]);
		ural_rf_write(sc, RAL_RF3, power << 7 | 0x38044);
		ural_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00280 : 0x00286);
		break;

	case RAL_RF_2524:
		ural_rf_write(sc, RAL_RF1, 0x0c808);
		ural_rf_write(sc, RAL_RF2, ural_rf2524_r2[chan - 1]);
		ural_rf_write(sc, RAL_RF3, power << 7 | 0x00040);
		ural_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00280 : 0x00286);
		break;

	case RAL_RF_2525:
		ural_rf_write(sc, RAL_RF1, 0x08808);
		ural_rf_write(sc, RAL_RF2, ural_rf2525_hi_r2[chan - 1]);
		ural_rf_write(sc, RAL_RF3, power << 7 | 0x18044);
		ural_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00280 : 0x00286);

		ural_rf_write(sc, RAL_RF1, 0x08808);
		ural_rf_write(sc, RAL_RF2, ural_rf2525_r2[chan - 1]);
		ural_rf_write(sc, RAL_RF3, power << 7 | 0x18044);
		ural_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00280 : 0x00286);
		break;

	case RAL_RF_2525E:
		ural_rf_write(sc, RAL_RF1, 0x08808);
		ural_rf_write(sc, RAL_RF2, ural_rf2525e_r2[chan - 1]);
		ural_rf_write(sc, RAL_RF3, power << 7 | 0x18044);
		ural_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00286 : 0x00282);
		break;

	case RAL_RF_2526:
		ural_rf_write(sc, RAL_RF2, ural_rf2526_hi_r2[chan - 1]);
		ural_rf_write(sc, RAL_RF4, (chan & 1) ? 0x00386 : 0x00381);
		ural_rf_write(sc, RAL_RF1, 0x08804);

		ural_rf_write(sc, RAL_RF2, ural_rf2526_r2[chan - 1]);
		ural_rf_write(sc, RAL_RF3, power << 7 | 0x18044);
		ural_rf_write(sc, RAL_RF4, (chan & 1) ? 0x00386 : 0x00381);
		break;

	/* dual-band RF */
	case RAL_RF_5222:
		for (i = 0; ural_rf5222[i].chan != chan; i++);

		ural_rf_write(sc, RAL_RF1, ural_rf5222[i].r1);
		ural_rf_write(sc, RAL_RF2, ural_rf5222[i].r2);
		ural_rf_write(sc, RAL_RF3, power << 7 | 0x00040);
		ural_rf_write(sc, RAL_RF4, ural_rf5222[i].r4);
		break;
	}

	if (ic->ic_opmode != IEEE80211_M_MONITOR &&
	    (ic->ic_flags & IEEE80211_F_SCAN) == 0) {
		/* set Japan filter bit for channel 14 */
		tmp = ural_bbp_read(sc, 70);

		tmp &= ~RAL_JAPAN_FILTER;
		if (chan == 14)
			tmp |= RAL_JAPAN_FILTER;

		ural_bbp_write(sc, 70, tmp);

		/* clear CRC errors */
		ural_read(sc, RAL_STA_CSR0);

		ural_pause(sc, hz / 100);
		ural_disable_rf_tune(sc);
	}

	/* XXX doesn't belong here */
	/* update basic rate set */
	ural_set_basicrates(sc, c);

	/* give the hardware some time to do the switchover */
	ural_pause(sc, hz / 100);
}