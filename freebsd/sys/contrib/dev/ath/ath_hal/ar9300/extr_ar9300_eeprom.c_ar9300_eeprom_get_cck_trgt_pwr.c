#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  size_t u_int16_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {TYPE_2__* cal_target_power_cck; int /*<<< orphan*/ * cal_target_freqbin_cck; } ;
typedef  TYPE_1__ ar9300_eeprom_t ;
struct TYPE_6__ {TYPE_1__ ah_eeprom; } ;
struct TYPE_5__ {int /*<<< orphan*/ * t_pow2x; } ;
typedef  TYPE_2__ CAL_TARGET_POWER_LEG ;

/* Variables and functions */
 TYPE_3__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  FBIN2FREQ (int /*<<< orphan*/ ,int) ; 
 int OSPREY_NUM_2G_CCK_TARGET_POWERS ; 
 scalar_t__ interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

u_int8_t
ar9300_eeprom_get_cck_trgt_pwr(struct ath_hal *ah, u_int16_t rate_index,
    u_int16_t freq)
{
    u_int16_t            num_piers = OSPREY_NUM_2G_CCK_TARGET_POWERS, i;
    int32_t              target_power_array[OSPREY_NUM_2G_CCK_TARGET_POWERS];
    int32_t              freq_array[OSPREY_NUM_2G_CCK_TARGET_POWERS]; 
    ar9300_eeprom_t      *eep = &AH9300(ah)->ah_eeprom;
    u_int8_t             *p_freq_bin = eep->cal_target_freqbin_cck;
    CAL_TARGET_POWER_LEG *p_eeprom_target_pwr = eep->cal_target_power_cck;

    /*
     * create array of channels and targetpower from
     * targetpower piers stored on eeprom
     */
    for (i = 0; i < num_piers; i++) {
        freq_array[i] = FBIN2FREQ(p_freq_bin[i], 1);
        target_power_array[i] = p_eeprom_target_pwr[i].t_pow2x[rate_index];
    }

    /* interpolate to get target power for given frequency */
    return
        ((u_int8_t)interpolate(
            (int32_t)freq, freq_array, target_power_array, num_piers));
}