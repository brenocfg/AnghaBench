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
struct ieee80211_channel {int dummy; } ;
struct ath_hal_9300 {int ah_supp_cals; } ;
struct ath_hal {int dummy; } ;
typedef  int HAL_CAL_TYPES ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
#define  IQ_MISMATCH_CAL 129 
#define  TEMP_COMP_CAL 128 

__attribute__((used)) inline static HAL_BOOL
ar9300_is_cal_supp(struct ath_hal *ah, const struct ieee80211_channel *chan,
    HAL_CAL_TYPES cal_type) 
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    HAL_BOOL retval = AH_FALSE;

    switch (cal_type & ahp->ah_supp_cals) {
    case IQ_MISMATCH_CAL:
        /* Run IQ Mismatch for non-CCK only */
        if (!IEEE80211_IS_CHAN_B(chan)) {
            retval = AH_TRUE;
        }
        break;
    case TEMP_COMP_CAL:
        retval = AH_TRUE;
        break;
    }

    return retval;
}