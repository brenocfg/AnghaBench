#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
typedef  TYPE_1__ HAL_CHANNEL_INTERNAL ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_SREV_HONEYBEE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_HORNET (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_WASP (struct ath_hal*) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  ar9300_ant_ctrl_apply (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_attenuation_apply (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_drive_strength_apply (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_internal_regulator_apply (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_quick_drop_apply (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_thermometer_apply (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_tuning_caps_apply (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_tx_end_to_xpab_off_apply (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_x_lNA_bias_strength_apply (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_xpa_bias_level_apply (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_xpa_timing_control_apply (struct ath_hal*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ath_hal_checkchannel (struct ath_hal*,struct ieee80211_channel const*) ; 

HAL_BOOL
ar9300_eeprom_set_board_values(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
    HAL_CHANNEL_INTERNAL *ichan = ath_hal_checkchannel(ah, chan);

    ar9300_xpa_bias_level_apply(ah, IEEE80211_IS_CHAN_2GHZ(chan));

    ar9300_xpa_timing_control_apply(ah, IEEE80211_IS_CHAN_2GHZ(chan));

    ar9300_ant_ctrl_apply(ah, IEEE80211_IS_CHAN_2GHZ(chan));
    ar9300_drive_strength_apply(ah);

    ar9300_x_lNA_bias_strength_apply(ah, IEEE80211_IS_CHAN_2GHZ(chan));

	/* wait for Poseidon internal regular turnning */
    /* for Hornet we move it before initPLL to avoid an access issue */
    /* Function not used when EMULATION. */
    if (!AR_SREV_HORNET(ah) && !AR_SREV_WASP(ah) && !AR_SREV_HONEYBEE(ah)) {
        ar9300_internal_regulator_apply(ah);
    }

    ar9300_attenuation_apply(ah, ichan->channel);
    ar9300_quick_drop_apply(ah, ichan->channel);
    ar9300_thermometer_apply(ah);
    if(!AR_SREV_WASP(ah))
    {
        ar9300_tuning_caps_apply(ah);
    }

    ar9300_tx_end_to_xpab_off_apply(ah, ichan->channel);

    return AH_TRUE;
}