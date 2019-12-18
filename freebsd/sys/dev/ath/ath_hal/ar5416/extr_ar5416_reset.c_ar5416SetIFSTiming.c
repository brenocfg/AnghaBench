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
typedef  int uint32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int AR5416_HALF_RATE_USEC_40 ; 
 int AR5416_HALF_RATE_USEC_44 ; 
 int AR5416_IFS_EIFS_HALF_RATE_40 ; 
 int AR5416_IFS_EIFS_HALF_RATE_44 ; 
 int AR5416_IFS_EIFS_QUARTER_RATE_40 ; 
 int AR5416_IFS_EIFS_QUARTER_RATE_44 ; 
 int AR5416_IFS_SLOT_HALF_RATE_40 ; 
 int AR5416_IFS_SLOT_HALF_RATE_44 ; 
 int AR5416_IFS_SLOT_QUARTER_RATE_40 ; 
 int AR5416_IFS_SLOT_QUARTER_RATE_44 ; 
 int AR5416_INIT_USEC_40 ; 
 int AR5416_INIT_USEC_44 ; 
 int AR5416_QUARTER_RATE_USEC_40 ; 
 int AR5416_QUARTER_RATE_USEC_44 ; 
 int AR5416_RX_NON_FULL_RATE_LATENCY ; 
 int AR5416_TX_HALF_RATE_LATENCY ; 
 int AR5416_TX_QUARTER_RATE_LATENCY ; 
 int AR5416_USEC_RX_LAT_S ; 
 int AR5416_USEC_TX_LAT_S ; 
 int /*<<< orphan*/  AR_D_GBL_IFS_EIFS ; 
 int /*<<< orphan*/  AR_D_GBL_IFS_MISC ; 
 int /*<<< orphan*/  AR_D_GBL_IFS_MISC_USEC_DURATION ; 
 int /*<<< orphan*/  AR_D_GBL_IFS_SLOT ; 
 int /*<<< orphan*/  AR_USEC ; 
 int AR_USEC_USEC32 ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 scalar_t__ IS_5GHZ_FAST_CLOCK_EN (struct ath_hal*,struct ieee80211_channel const*) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar5416SetIFSTiming(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	uint32_t txLat, rxLat, usec, slot, refClock, eifs, init_usec;
	int clk_44 = 0;

	HALASSERT(IEEE80211_IS_CHAN_HALF(chan) ||
	    IEEE80211_IS_CHAN_QUARTER(chan));

	/* 2GHz and 5GHz fast clock - 44MHz; else 40MHz */
	if (IEEE80211_IS_CHAN_2GHZ(chan))
		clk_44 = 1;
	else if (IEEE80211_IS_CHAN_5GHZ(chan) &&
	    IS_5GHZ_FAST_CLOCK_EN(ah, chan))
		clk_44 = 1;

	/* XXX does this need save/restoring for the 11n chips? */
	/*
	 * XXX TODO: should mask out the txlat/rxlat/usec values?
	 */
	refClock = OS_REG_READ(ah, AR_USEC) & AR_USEC_USEC32;

	/*
	 * XXX This really should calculate things, not use
	 * hard coded values! Ew.
	 */
	if (IEEE80211_IS_CHAN_HALF(chan)) {
		if (clk_44) {
			slot = AR5416_IFS_SLOT_HALF_RATE_44;
			rxLat = AR5416_RX_NON_FULL_RATE_LATENCY <<
			    AR5416_USEC_RX_LAT_S;
			txLat = AR5416_TX_HALF_RATE_LATENCY <<
			    AR5416_USEC_TX_LAT_S;
			usec = AR5416_HALF_RATE_USEC_44;
			eifs = AR5416_IFS_EIFS_HALF_RATE_44;
			init_usec = AR5416_INIT_USEC_44 >> 1;
		} else {
			slot = AR5416_IFS_SLOT_HALF_RATE_40;
			rxLat = AR5416_RX_NON_FULL_RATE_LATENCY <<
			    AR5416_USEC_RX_LAT_S;
			txLat = AR5416_TX_HALF_RATE_LATENCY <<
			    AR5416_USEC_TX_LAT_S;
			usec = AR5416_HALF_RATE_USEC_40;
			eifs = AR5416_IFS_EIFS_HALF_RATE_40;
			init_usec = AR5416_INIT_USEC_40 >> 1;
		}
	} else { /* quarter rate */
		if (clk_44) {
			slot = AR5416_IFS_SLOT_QUARTER_RATE_44;
			rxLat = AR5416_RX_NON_FULL_RATE_LATENCY <<
			    AR5416_USEC_RX_LAT_S;
			txLat = AR5416_TX_QUARTER_RATE_LATENCY <<
			    AR5416_USEC_TX_LAT_S;
			usec = AR5416_QUARTER_RATE_USEC_44;
			eifs = AR5416_IFS_EIFS_QUARTER_RATE_44;
			init_usec = AR5416_INIT_USEC_44 >> 2;
		} else {
			slot = AR5416_IFS_SLOT_QUARTER_RATE_40;
			rxLat = AR5416_RX_NON_FULL_RATE_LATENCY <<
			    AR5416_USEC_RX_LAT_S;
			txLat = AR5416_TX_QUARTER_RATE_LATENCY <<
			    AR5416_USEC_TX_LAT_S;
			usec = AR5416_QUARTER_RATE_USEC_40;
			eifs = AR5416_IFS_EIFS_QUARTER_RATE_40;
			init_usec = AR5416_INIT_USEC_40 >> 2;
		}
	}

	/* XXX verify these! */
	OS_REG_WRITE(ah, AR_USEC, (usec | refClock | txLat | rxLat));
	OS_REG_WRITE(ah, AR_D_GBL_IFS_SLOT, slot);
	OS_REG_WRITE(ah, AR_D_GBL_IFS_EIFS, eifs);
	OS_REG_RMW_FIELD(ah, AR_D_GBL_IFS_MISC,
	    AR_D_GBL_IFS_MISC_USEC_DURATION, init_usec);
}