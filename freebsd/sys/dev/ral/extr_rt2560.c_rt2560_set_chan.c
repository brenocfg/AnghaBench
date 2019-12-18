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
typedef  int u_int ;
struct ieee80211com {int ic_txpowlimit; int ic_flags; } ;
struct rt2560_softc {int rf_rev; int /*<<< orphan*/ * txpow; struct ieee80211com sc_ic; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_2__ {int chan; int r1; int r2; int r4; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (struct rt2560_softc*,int,char*,int,int) ; 
 int IEEE80211_CHAN_ANY ; 
 int IEEE80211_F_SCAN ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RAL_READ (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_RF1 ; 
 int /*<<< orphan*/  RAL_RF2 ; 
 int /*<<< orphan*/  RAL_RF3 ; 
 int /*<<< orphan*/  RAL_RF4 ; 
 int /*<<< orphan*/  RT2560_CNT0 ; 
 int RT2560_JAPAN_FILTER ; 
#define  RT2560_RF_2522 134 
#define  RT2560_RF_2523 133 
#define  RT2560_RF_2524 132 
#define  RT2560_RF_2525 131 
#define  RT2560_RF_2525E 130 
#define  RT2560_RF_2526 129 
#define  RT2560_RF_5222 128 
 int ieee80211_chan2ieee (struct ieee80211com*,struct ieee80211_channel*) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int rt2560_bbp_read (struct rt2560_softc*,int) ; 
 int /*<<< orphan*/  rt2560_bbp_write (struct rt2560_softc*,int,int) ; 
 int* rt2560_rf2522_r2 ; 
 int* rt2560_rf2523_r2 ; 
 int* rt2560_rf2524_r2 ; 
 int* rt2560_rf2525_hi_r2 ; 
 int* rt2560_rf2525_r2 ; 
 int* rt2560_rf2525e_r2 ; 
 int* rt2560_rf2526_hi_r2 ; 
 int* rt2560_rf2526_r2 ; 
 TYPE_1__* rt2560_rf5222 ; 
 int /*<<< orphan*/  rt2560_rf_write (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rt2560_set_chan(struct rt2560_softc *sc, struct ieee80211_channel *c)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint8_t power, tmp;
	u_int i, chan;

	chan = ieee80211_chan2ieee(ic, c);
	KASSERT(chan != 0 && chan != IEEE80211_CHAN_ANY, ("chan 0x%x", chan));

	if (IEEE80211_IS_CHAN_2GHZ(c))
		power = min(sc->txpow[chan - 1], 31);
	else
		power = 31;

	/* adjust txpower using ifconfig settings */
	power -= (100 - ic->ic_txpowlimit) / 8;

	DPRINTFN(sc, 2, "setting channel to %u, txpower to %u\n", chan, power);

	switch (sc->rf_rev) {
	case RT2560_RF_2522:
		rt2560_rf_write(sc, RAL_RF1, 0x00814);
		rt2560_rf_write(sc, RAL_RF2, rt2560_rf2522_r2[chan - 1]);
		rt2560_rf_write(sc, RAL_RF3, power << 7 | 0x00040);
		break;

	case RT2560_RF_2523:
		rt2560_rf_write(sc, RAL_RF1, 0x08804);
		rt2560_rf_write(sc, RAL_RF2, rt2560_rf2523_r2[chan - 1]);
		rt2560_rf_write(sc, RAL_RF3, power << 7 | 0x38044);
		rt2560_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00280 : 0x00286);
		break;

	case RT2560_RF_2524:
		rt2560_rf_write(sc, RAL_RF1, 0x0c808);
		rt2560_rf_write(sc, RAL_RF2, rt2560_rf2524_r2[chan - 1]);
		rt2560_rf_write(sc, RAL_RF3, power << 7 | 0x00040);
		rt2560_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00280 : 0x00286);
		break;

	case RT2560_RF_2525:
		rt2560_rf_write(sc, RAL_RF1, 0x08808);
		rt2560_rf_write(sc, RAL_RF2, rt2560_rf2525_hi_r2[chan - 1]);
		rt2560_rf_write(sc, RAL_RF3, power << 7 | 0x18044);
		rt2560_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00280 : 0x00286);

		rt2560_rf_write(sc, RAL_RF1, 0x08808);
		rt2560_rf_write(sc, RAL_RF2, rt2560_rf2525_r2[chan - 1]);
		rt2560_rf_write(sc, RAL_RF3, power << 7 | 0x18044);
		rt2560_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00280 : 0x00286);
		break;

	case RT2560_RF_2525E:
		rt2560_rf_write(sc, RAL_RF1, 0x08808);
		rt2560_rf_write(sc, RAL_RF2, rt2560_rf2525e_r2[chan - 1]);
		rt2560_rf_write(sc, RAL_RF3, power << 7 | 0x18044);
		rt2560_rf_write(sc, RAL_RF4, (chan == 14) ? 0x00286 : 0x00282);
		break;

	case RT2560_RF_2526:
		rt2560_rf_write(sc, RAL_RF2, rt2560_rf2526_hi_r2[chan - 1]);
		rt2560_rf_write(sc, RAL_RF4, (chan & 1) ? 0x00386 : 0x00381);
		rt2560_rf_write(sc, RAL_RF1, 0x08804);

		rt2560_rf_write(sc, RAL_RF2, rt2560_rf2526_r2[chan - 1]);
		rt2560_rf_write(sc, RAL_RF3, power << 7 | 0x18044);
		rt2560_rf_write(sc, RAL_RF4, (chan & 1) ? 0x00386 : 0x00381);
		break;

	/* dual-band RF */
	case RT2560_RF_5222:
		for (i = 0; rt2560_rf5222[i].chan != chan; i++);

		rt2560_rf_write(sc, RAL_RF1, rt2560_rf5222[i].r1);
		rt2560_rf_write(sc, RAL_RF2, rt2560_rf5222[i].r2);
		rt2560_rf_write(sc, RAL_RF3, power << 7 | 0x00040);
		rt2560_rf_write(sc, RAL_RF4, rt2560_rf5222[i].r4);
		break;
	default: 
 	        printf("unknown ral rev=%d\n", sc->rf_rev);
	}

	/* XXX */
	if ((ic->ic_flags & IEEE80211_F_SCAN) == 0) {
		/* set Japan filter bit for channel 14 */
		tmp = rt2560_bbp_read(sc, 70);

		tmp &= ~RT2560_JAPAN_FILTER;
		if (chan == 14)
			tmp |= RT2560_JAPAN_FILTER;

		rt2560_bbp_write(sc, 70, tmp);

		/* clear CRC errors */
		RAL_READ(sc, RT2560_CNT0);
	}
}