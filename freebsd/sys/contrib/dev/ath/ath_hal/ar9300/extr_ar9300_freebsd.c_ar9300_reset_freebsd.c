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
struct ieee80211_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  halRxChainMask; int /*<<< orphan*/  halTxChainMask; } ;
struct ath_hal_private {TYPE_1__ ah_caps; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int /*<<< orphan*/  HAL_RESET_TYPE ;
typedef  int /*<<< orphan*/  HAL_OPMODE ;
typedef  int /*<<< orphan*/  HAL_HT_MACMODE ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 struct ath_hal_private* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  HAL_HT_EXTPROTSPACING_20 ; 
 int /*<<< orphan*/  HAL_HT_MACMODE_20 ; 
 int /*<<< orphan*/  HAL_HT_MACMODE_2040 ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ar9300_reset (struct ath_hal*,int /*<<< orphan*/ ,struct ieee80211_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_reset_freebsd(struct ath_hal *ah, HAL_OPMODE opmode,
    struct ieee80211_channel *chan, HAL_BOOL bChannelChange,
    HAL_RESET_TYPE resetType,
    HAL_STATUS *status)
{
	HAL_BOOL r;
	HAL_HT_MACMODE macmode;
	struct ath_hal_private  *ap  = AH_PRIVATE(ah);

	macmode =
	    IEEE80211_IS_CHAN_HT40(chan) ?
	        HAL_HT_MACMODE_2040 : HAL_HT_MACMODE_20;

	r = ar9300_reset(ah, opmode, chan, macmode,
	    ap->ah_caps.halTxChainMask,
	    ap->ah_caps.halRxChainMask,
	    HAL_HT_EXTPROTSPACING_20, /* always 20Mhz channel spacing */
	    bChannelChange,
	    status,
	    AH_FALSE);       /* XXX should really extend ath_hal_reset() */

	return (r);
}