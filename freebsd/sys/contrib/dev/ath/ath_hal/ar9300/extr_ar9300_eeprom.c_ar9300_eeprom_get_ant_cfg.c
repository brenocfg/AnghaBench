#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  int u_int16_t ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_8__ {int version; } ;
struct TYPE_6__ {TYPE_4__ base_eep_header; TYPE_3__* modal_header; } ;
struct TYPE_5__ {TYPE_2__ def; } ;
struct ath_hal_9300 {TYPE_1__ ah_eeprom; } ;
typedef  TYPE_2__ ar9300_eeprom_t ;
struct TYPE_7__ {int ant_ctrl_common; int /*<<< orphan*/  use_ant1; } ;
typedef  TYPE_3__ MODAL_EEPDEF_HEADER ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  TYPE_4__ BASE_EEPDEF_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_EINVAL ; 
 int /*<<< orphan*/  HAL_OK ; 
 size_t IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 

HAL_STATUS
ar9300_eeprom_get_ant_cfg(struct ath_hal_9300 *ahp,
  const struct ieee80211_channel *chan,
  u_int8_t index, u_int16_t *config)
{
#if 0
    ar9300_eeprom_t  *eep = &ahp->ah_eeprom.def;
    MODAL_EEPDEF_HEADER *p_modal = &(eep->modal_header[IEEE80211_IS_CHAN_2GHZ(chan)]);
    BASE_EEPDEF_HEADER  *p_base  = &eep->base_eep_header;

    switch (index) {
    case 0:
        *config = p_modal->ant_ctrl_common & 0xFFFF;
        return HAL_OK;
    case 1:
        if (p_base->version >= 0x0E0D) {
            if (p_modal->use_ant1) {
                *config = ((p_modal->ant_ctrl_common & 0xFFFF0000) >> 16);
                return HAL_OK;
            }
        }
        break;
    default:
        break;
    }
#endif
    return HAL_EINVAL;
}