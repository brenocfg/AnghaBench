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
typedef  scalar_t__ u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct ath_hal {scalar_t__ ah_magic; } ;
typedef  scalar_t__ int8_t ;
typedef  int /*<<< orphan*/  HAL_STATUS ;

/* Variables and functions */
 scalar_t__ AR9300_MAGIC ; 
 scalar_t__ AR9300_MAX_RATE_POWER ; 
 int /*<<< orphan*/  HAL_OK ; 
 int ar9300_rate_size ; 
 int /*<<< orphan*/  ar9300_set_target_power_from_eeprom (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__*) ; 

HAL_STATUS
ath_hal_get_rate_power_limit_from_eeprom(struct ath_hal *ah, u_int16_t freq,
                                        int8_t *max_rate_power, int8_t *min_rate_power)
{
    /*
     * Used for AR9300 series chip only
     */
    if (ah->ah_magic == AR9300_MAGIC) {
        u_int8_t target_rate_power_limit_val_t2[ar9300_rate_size];
        int i;

        *max_rate_power = 0;
        *min_rate_power = AR9300_MAX_RATE_POWER;

        ar9300_set_target_power_from_eeprom(ah, freq, target_rate_power_limit_val_t2);

        for (i=0; i<ar9300_rate_size; i++) {
            if (target_rate_power_limit_val_t2[i] > *max_rate_power)
                *max_rate_power = target_rate_power_limit_val_t2[i];
            if (target_rate_power_limit_val_t2[i] < *min_rate_power)
                *min_rate_power = target_rate_power_limit_val_t2[i];
        }
    } else {
        *max_rate_power = 0;
        *min_rate_power = 0;
    }

    return HAL_OK;
}