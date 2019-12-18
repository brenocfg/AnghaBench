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
struct TYPE_8__ {int version; } ;
struct TYPE_6__ {TYPE_4__ base_eep_header; TYPE_3__* modal_header; } ;
struct TYPE_5__ {TYPE_2__ def; } ;
struct ath_hal_9300 {TYPE_1__ ah_eeprom; } ;
typedef  TYPE_2__ ar9300_eeprom_t ;
struct TYPE_7__ {scalar_t__ use_ant1; } ;
typedef  TYPE_3__ MODAL_EEPDEF_HEADER ;
typedef  scalar_t__ HAL_FREQ_BAND ;
typedef  TYPE_4__ BASE_EEPDEF_HEADER ;

/* Variables and functions */
 scalar_t__ HAL_FREQ_BAND_2GHZ ; 

u_int8_t
ar9300_eeprom_get_num_ant_config(struct ath_hal_9300 *ahp,
    HAL_FREQ_BAND freq_band)
{
#if 0
    ar9300_eeprom_t  *eep = &ahp->ah_eeprom.def;
    MODAL_EEPDEF_HEADER *p_modal =
        &(eep->modal_header[HAL_FREQ_BAND_2GHZ == freq_band]);
    BASE_EEPDEF_HEADER  *p_base  = &eep->base_eep_header;
    u_int8_t         num_ant_config;

    num_ant_config = 1; /* default antenna configuration */

    if (p_base->version >= 0x0E0D) {
        if (p_modal->use_ant1) {
            num_ant_config += 1;
        }
    }

    return num_ant_config;
#else
    return 1;
#endif
}