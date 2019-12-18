#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ieee80211_channel {int /*<<< orphan*/  ic_freq; } ;
struct ath_hal {int dummy; } ;
struct TYPE_5__ {struct ieee80211_channel const* ah_curchan; } ;
struct TYPE_4__ {int synth_center; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  TYPE_1__ CHAN_CENTERS ;

/* Variables and functions */
 int /*<<< orphan*/  AH_MARK_SETCHANNEL ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_AN_SYNTH9 ; 
 int /*<<< orphan*/  AR_AN_SYNTH9_REFDIVA ; 
 int /*<<< orphan*/  AR_EEP_FRAC_N_5G ; 
 int /*<<< orphan*/  AR_PHY_CCK_TX_CTRL ; 
 int AR_PHY_CCK_TX_CTRL_JAPAN ; 
 int /*<<< orphan*/  AR_PHY_SYNTH_CONTROL ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  OS_A_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_MARK (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5416GetChannelCenters (struct ath_hal*,struct ieee80211_channel const*,TYPE_1__*) ; 
 scalar_t__ ath_hal_eepromGet (struct ath_hal*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static HAL_BOOL
ar9280SetChannel(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	uint16_t bMode, fracMode, aModeRefSel = 0;
	uint32_t freq, ndiv, channelSel = 0, channelFrac = 0, reg32 = 0;
	CHAN_CENTERS centers;
	uint32_t refDivA = 24;
	uint8_t frac_n_5g;

	OS_MARK(ah, AH_MARK_SETCHANNEL, chan->ic_freq);

	ar5416GetChannelCenters(ah, chan, &centers);
	freq = centers.synth_center;

	reg32 = OS_REG_READ(ah, AR_PHY_SYNTH_CONTROL);
	reg32 &= 0xc0000000;

	if (ath_hal_eepromGet(ah, AR_EEP_FRAC_N_5G, &frac_n_5g) != HAL_OK)
		frac_n_5g = 0;

	if (freq < 4800) {     /* 2 GHz, fractional mode */
		uint32_t txctl;

		bMode = 1;
		fracMode = 1;
		aModeRefSel = 0;       
		channelSel = (freq * 0x10000)/15;

		txctl = OS_REG_READ(ah, AR_PHY_CCK_TX_CTRL);
		if (freq == 2484) {
			/* Enable channel spreading for channel 14 */
			OS_REG_WRITE(ah, AR_PHY_CCK_TX_CTRL,
			    txctl | AR_PHY_CCK_TX_CTRL_JAPAN);
		} else {
			OS_REG_WRITE(ah, AR_PHY_CCK_TX_CTRL,
			    txctl &~ AR_PHY_CCK_TX_CTRL_JAPAN);
		}     
	} else {
		bMode = 0;
		fracMode = 0;

		switch (frac_n_5g) {
		case 0:
			/*
			 * Enable fractional mode for half/quarter rate
			 * channels.
			 *
			 * This is from the Linux ath9k code, rather than
			 * the Atheros HAL code.
			 */
			if (IEEE80211_IS_CHAN_QUARTER(chan) ||
			    IEEE80211_IS_CHAN_HALF(chan))
				aModeRefSel = 0;
			else if ((freq % 20) == 0) {
				aModeRefSel = 3;
			} else if ((freq % 10) == 0) {
				aModeRefSel = 2;
			}
			if (aModeRefSel) break;
		case 1:
		default:
			aModeRefSel = 0;
			/* Enable 2G (fractional) mode for channels which are 5MHz spaced */

			/*
			 * Workaround for talking on PSB non-5MHz channels;
			 * the pre-Merlin chips only had a 2.5MHz channel
			 * spacing so some channels aren't reachable.

			 *
			 * This interoperates on the quarter rate channels
			 * with the AR5112 and later RF synths.  Please note
			 * that the synthesiser isn't able to completely
			 * accurately represent these frequencies (as the
			 * resolution in this reference is 2.5MHz) and thus
			 * it will be slightly "off centre."  This matches
			 * the same slightly incorrect centre frequency
			 * behaviour that the AR5112 and later channel
			 * selection code has.
			 *
			 * This also interoperates with the AR5416
			 * synthesiser modification for programming
			 * fractional frequencies in 5GHz mode.  However
			 * that modification is also disabled by default.
			 *
			 * This is disabled because it hasn't been tested for
			 * regulatory compliance and neither have the NICs
			 * which would use it.  So if you enable this code,
			 * you must first ensure that you've re-certified the
			 * NICs in question beforehand or you will be
			 * violating your local regulatory rules and breaking
			 * the law.
			 */
#if 0
			if (freq % 5 == 0) {
#endif
				/* Normal */
				fracMode = 1;
				refDivA = 1;
				channelSel = (freq * 0x8000)/15;
#if 0
			} else {
				/* Offset by 500KHz */
				uint32_t f, ch, ch2;

				fracMode = 1;
				refDivA = 1;

				/* Calculate the "adjusted" frequency */
				f = freq - 2;
				ch = (((f - 4800) * 10) / 25) + 1;

				ch2 = ((ch * 25) / 5) + 9600;
				channelSel = (ch2 * 0x4000) / 15;
				//ath_hal_printf(ah,
				//    "%s: freq=%d, ch=%d, ch2=%d, "
				//    "channelSel=%d\n",
				//    __func__, freq, ch, ch2, channelSel);
			}
#endif

			/* RefDivA setting */
			OS_A_REG_RMW_FIELD(ah, AR_AN_SYNTH9,
			    AR_AN_SYNTH9_REFDIVA, refDivA);
		}

		if (!fracMode) {
			ndiv = (freq * (refDivA >> aModeRefSel))/60;
			channelSel =  ndiv & 0x1ff;         
			channelFrac = (ndiv & 0xfffffe00) * 2;
			channelSel = (channelSel << 17) | channelFrac;
		}
	}

	reg32 = reg32 | (bMode << 29) | (fracMode << 28) |
	    (aModeRefSel << 26) | (channelSel);

	OS_REG_WRITE(ah, AR_PHY_SYNTH_CONTROL, reg32);

	AH_PRIVATE(ah)->ah_curchan = chan;

	return AH_TRUE;
}