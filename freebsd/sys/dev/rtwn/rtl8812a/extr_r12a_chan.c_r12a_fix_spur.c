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
typedef  int uint16_t ;
struct rtwn_softc {struct r12a_softc* sc_priv; } ;
struct r12a_softc {int chip; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  R12A_ADC_BUF_CLK ; 
 int R12A_CHIP_C_CUT ; 
 int /*<<< orphan*/  R12A_RFMOD ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 
 int rtwn_chan2centieee (struct ieee80211_channel*) ; 

void
r12a_fix_spur(struct rtwn_softc *sc, struct ieee80211_channel *c)
{
	struct r12a_softc *rs = sc->sc_priv;
	uint16_t chan = rtwn_chan2centieee(c);

	if (rs->chip & R12A_CHIP_C_CUT) {
		if (IEEE80211_IS_CHAN_HT40(c) && chan == 11) {
			rtwn_bb_setbits(sc, R12A_RFMOD, 0, 0xc00);
			rtwn_bb_setbits(sc, R12A_ADC_BUF_CLK, 0, 0x40000000);
		} else {
			rtwn_bb_setbits(sc, R12A_RFMOD, 0x400, 0x800);

			if (!IEEE80211_IS_CHAN_HT40(c) &&	/* 20 MHz */
			    (chan == 13 || chan == 14)) {
				rtwn_bb_setbits(sc, R12A_RFMOD, 0, 0x300);
				rtwn_bb_setbits(sc, R12A_ADC_BUF_CLK,
				    0, 0x40000000);
			} else {	/* !80 Mhz */
				rtwn_bb_setbits(sc, R12A_RFMOD, 0x100, 0x200);
				rtwn_bb_setbits(sc, R12A_ADC_BUF_CLK,
				    0x40000000, 0);
			}
		}
	} else {
		/* Set ADC clock to 160M to resolve 2480 MHz spur. */
		if (!IEEE80211_IS_CHAN_HT40(c) &&	/* 20 MHz */
		    (chan == 13 || chan == 14))
			rtwn_bb_setbits(sc, R12A_RFMOD, 0, 0x300);
		else if (IEEE80211_IS_CHAN_2GHZ(c))
			rtwn_bb_setbits(sc, R12A_RFMOD, 0x100, 0x200);
	}
}