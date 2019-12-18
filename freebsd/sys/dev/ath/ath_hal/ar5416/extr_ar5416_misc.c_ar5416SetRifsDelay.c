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
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 scalar_t__ AH_FALSE ; 
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  AR_PHY_HEAVY_CLIP_FACTOR_RIFS ; 
 int AR_PHY_RIFS_INIT_DELAY ; 
 int /*<<< orphan*/  AR_PHY_SEARCH_START_DELAY ; 
 int /*<<< orphan*/  AR_SREV_HOWL (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_SOWL (struct ath_hal*) ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

HAL_BOOL
ar5416SetRifsDelay(struct ath_hal *ah, const struct ieee80211_channel *chan,
    HAL_BOOL enable)
{
	uint32_t val;
	HAL_BOOL is_chan_2g = AH_FALSE;
	HAL_BOOL is_ht40 = AH_FALSE;

	if (chan)
		is_chan_2g = IEEE80211_IS_CHAN_2GHZ(chan);

	if (chan)
		is_ht40 = IEEE80211_IS_CHAN_HT40(chan);

	/* Only support disabling RIFS delay for now */
	HALASSERT(enable == AH_FALSE);

	if (enable == AH_TRUE)
		return AH_FALSE;

	/* Change RIFS init delay to 0 */
	val = OS_REG_READ(ah, AR_PHY_HEAVY_CLIP_FACTOR_RIFS);
	val &= ~AR_PHY_RIFS_INIT_DELAY;
	OS_REG_WRITE(ah, AR_PHY_HEAVY_CLIP_FACTOR_RIFS, val);

	/*
	 * For Owl, RIFS RX parameters are controlled differently;
	 * it isn't enabled in the inivals by default.
	 *
	 * For Sowl/Howl, RIFS RX is enabled in the inivals by default;
	 * the following code sets them back to non-RIFS values.
	 *
	 * For > Sowl/Howl, RIFS RX can be left on by default and so
	 * this function shouldn't be called.
	 */
	if ((! AR_SREV_SOWL(ah)) && (! AR_SREV_HOWL(ah)))
		return AH_TRUE;

	/* Reset search delay to default values */
	if (is_chan_2g)
		if (is_ht40)
			OS_REG_WRITE(ah, AR_PHY_SEARCH_START_DELAY, 0x268);
		else
			OS_REG_WRITE(ah, AR_PHY_SEARCH_START_DELAY, 0x134);
	else
		if (is_ht40)
			OS_REG_WRITE(ah, AR_PHY_SEARCH_START_DELAY, 0x370);
		else
			OS_REG_WRITE(ah, AR_PHY_SEARCH_START_DELAY, 0x1b8);

	return AH_TRUE;
}