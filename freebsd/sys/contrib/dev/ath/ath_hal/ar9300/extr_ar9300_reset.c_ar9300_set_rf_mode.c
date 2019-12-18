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
typedef  int u_int32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int ah_hwp; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 
 struct ieee80211_channel* AH_NULL ; 
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int AR_PHY_MODE_DYNAMIC ; 
 int AR_PHY_MODE_DYN_CCK_DISABLE ; 
 int AR_PHY_MODE_OFDM ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
#define  HAL_TRUE_CHIP 128 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_B (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_G (struct ieee80211_channel*) ; 
 scalar_t__ IS_5GHZ_FAST_CLOCK_EN (struct ath_hal*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ar9300_set_rf_mode(struct ath_hal *ah, struct ieee80211_channel *chan)
{
    u_int32_t rf_mode = 0;

    if (chan == AH_NULL) {
        return;
    }
    switch (AH9300(ah)->ah_hwp) {
    case HAL_TRUE_CHIP:
        rf_mode |= (IEEE80211_IS_CHAN_B(chan) || IEEE80211_IS_CHAN_G(chan)) ?
            AR_PHY_MODE_DYNAMIC : AR_PHY_MODE_OFDM;
        break;
    default:
        HALASSERT(0);
        break;
    }
    /*  Phy mode bits for 5GHz channels requiring Fast Clock */
    if ( IS_5GHZ_FAST_CLOCK_EN(ah, chan)) {
        rf_mode |= (AR_PHY_MODE_DYNAMIC | AR_PHY_MODE_DYN_CCK_DISABLE);
    }
    OS_REG_WRITE(ah, AR_PHY_MODE, rf_mode);
}