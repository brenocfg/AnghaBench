#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ieee80211_channel {int /*<<< orphan*/  ic_freq; } ;
struct ath_hal {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ah_ini_cckFirNormal; int /*<<< orphan*/  ah_ini_cckFirJapan2484; } ;
struct TYPE_6__ {struct ieee80211_channel const* ah_curchan; } ;
struct TYPE_5__ {int synth_center; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  TYPE_1__ CHAN_CENTERS ;

/* Variables and functions */
 TYPE_4__* AH9287 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_MARK_SETCHANNEL ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_AN_SYNTH9 ; 
 int /*<<< orphan*/  AR_AN_SYNTH9_REFDIVA ; 
 int /*<<< orphan*/  AR_PHY_CCK_TX_CTRL ; 
 int AR_PHY_CCK_TX_CTRL_JAPAN ; 
 int /*<<< orphan*/  AR_PHY_SYNTH_CONTROL ; 
 scalar_t__ AR_SREV_KIWI_11_OR_LATER (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_A_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_MARK (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5416GetChannelCenters (struct ath_hal*,struct ieee80211_channel const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ath_hal_ini_write (struct ath_hal*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static HAL_BOOL
ar9287SetChannel(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	uint16_t bMode, fracMode, aModeRefSel = 0;
	uint32_t freq, ndiv, channelSel = 0, channelFrac = 0, reg32 = 0;
	CHAN_CENTERS centers;
	uint32_t refDivA = 24;

	OS_MARK(ah, AH_MARK_SETCHANNEL, chan->ic_freq);

	ar5416GetChannelCenters(ah, chan, &centers);
	freq = centers.synth_center;

	reg32 = OS_REG_READ(ah, AR_PHY_SYNTH_CONTROL);
	reg32 &= 0xc0000000;

	if (freq < 4800) {     /* 2 GHz, fractional mode */
		uint32_t txctl;
		int regWrites = 0;

		bMode = 1;
		fracMode = 1;
		aModeRefSel = 0;       
		channelSel = (freq * 0x10000)/15;

		if (AR_SREV_KIWI_11_OR_LATER(ah)) {
			if (freq == 2484) {
				ath_hal_ini_write(ah,
				    &AH9287(ah)->ah_ini_cckFirJapan2484, 1,
				    regWrites);
			} else {
				ath_hal_ini_write(ah,
				    &AH9287(ah)->ah_ini_cckFirNormal, 1,
				    regWrites);
			}
		}

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

		if ((freq % 20) == 0) {
			aModeRefSel = 3;
		} else if ((freq % 10) == 0) {
			aModeRefSel = 2;
		} else {
			aModeRefSel = 0;
			/*
			 * Enable 2G (fractional) mode for channels which
			 * are 5MHz spaced
			 */
			fracMode = 1;
			refDivA = 1;
			channelSel = (freq * 0x8000)/15;

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