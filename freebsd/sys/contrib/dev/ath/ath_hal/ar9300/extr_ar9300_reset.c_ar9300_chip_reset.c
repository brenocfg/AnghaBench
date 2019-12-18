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
struct ieee80211_channel {int /*<<< orphan*/  ic_freq; } ;
struct ath_hal_9300 {scalar_t__ ah_chip_full_sleep; } ;
struct TYPE_2__ {int ah_force_full_reset; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 scalar_t__ AH_FALSE ; 
 int /*<<< orphan*/  AH_MARK_CHIPRESET ; 
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  AR_CR ; 
 int AR_CR_RXE ; 
 int /*<<< orphan*/  AR_Q_TXE ; 
 scalar_t__ AR_SREV_HORNET (struct ath_hal*) ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int HAL_RESET_COLD ; 
 int HAL_RESET_WARM ; 
 int /*<<< orphan*/  OS_MARK (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_init_pll (struct ath_hal*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ar9300_internal_regulator_apply (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_set_power_mode (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ar9300_set_reset_reg (struct ath_hal*,int) ; 
 int /*<<< orphan*/  ar9300_set_rf_mode (struct ath_hal*,struct ieee80211_channel*) ; 

HAL_BOOL
ar9300_chip_reset(struct ath_hal *ah, struct ieee80211_channel *chan)
{
    struct ath_hal_9300     *ahp = AH9300(ah);
    int type = HAL_RESET_WARM;

    OS_MARK(ah, AH_MARK_CHIPRESET, chan ? chan->ic_freq : 0);

    /*
     * Warm reset is optimistic.
     *
     * If the TX/RX DMA engines aren't shut down (eg, they're
     * wedged) then we're better off doing a full cold reset
     * to try and shake that condition.
     */
    if (ahp->ah_chip_full_sleep ||
        (ah->ah_config.ah_force_full_reset == 1) ||
        OS_REG_READ(ah, AR_Q_TXE) ||
        (OS_REG_READ(ah, AR_CR) & AR_CR_RXE)) {
            type = HAL_RESET_COLD;
    }

    if (!ar9300_set_reset_reg(ah, type)) {
        return AH_FALSE;
    }

    /* Bring out of sleep mode (AGAIN) */
    if (!ar9300_set_power_mode(ah, HAL_PM_AWAKE, AH_TRUE)) {
        return AH_FALSE;
    }

    ahp->ah_chip_full_sleep = AH_FALSE;

    if (AR_SREV_HORNET(ah)) {
        ar9300_internal_regulator_apply(ah);
    }

    ar9300_init_pll(ah, chan);

    /*
     * Perform warm reset before the mode/PLL/turbo registers
     * are changed in order to deactivate the radio.  Mode changes
     * with an active radio can result in corrupted shifts to the
     * radio device.
     */
    ar9300_set_rf_mode(ah, chan);

    return AH_TRUE;
}