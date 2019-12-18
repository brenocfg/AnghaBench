#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal_9300 {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {scalar_t__ halNumAntCfg2GHz; scalar_t__ halNumAntCfg5GHz; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; struct ieee80211_channel* ah_curchan; } ;
typedef  scalar_t__ HAL_STATUS ;
typedef  int /*<<< orphan*/  HAL_CHANNEL_INTERNAL ;
typedef  TYPE_1__ HAL_CAPABILITIES ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_SWITCH_COM ; 
 scalar_t__ HAL_EINVAL ; 
 scalar_t__ HAL_OK ; 
 scalar_t__ IS_CHAN_2GHZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ar9300_eeprom_get_ant_cfg (struct ath_hal_9300*,struct ieee80211_channel const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ath_hal_checkchannel (struct ath_hal*,struct ieee80211_channel const*) ; 

HAL_STATUS
ar9300_select_ant_config(struct ath_hal *ah, u_int32_t cfg)
{
    struct ath_hal_9300     *ahp = AH9300(ah);
    const struct ieee80211_channel *chan = AH_PRIVATE(ah)->ah_curchan;
    HAL_CHANNEL_INTERNAL    *ichan = ath_hal_checkchannel(ah, chan);
    const HAL_CAPABILITIES  *p_cap = &AH_PRIVATE(ah)->ah_caps;
    u_int16_t               ant_config;
    u_int32_t               hal_num_ant_config;

    hal_num_ant_config = IS_CHAN_2GHZ(ichan) ?
        p_cap->halNumAntCfg2GHz: p_cap->halNumAntCfg5GHz;

    if (cfg < hal_num_ant_config) {
        if (HAL_OK == ar9300_eeprom_get_ant_cfg(ahp, chan, cfg, &ant_config)) {
            OS_REG_WRITE(ah, AR_PHY_SWITCH_COM, ant_config);
            return HAL_OK;
        }
    }

    return HAL_EINVAL;
}