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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal_9300 {scalar_t__ ah_chip_full_sleep; } ;
struct ath_hal {int dummy; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  HAL_PM_FULL_SLEEP ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_set_power_mode (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int32_t ar9300_get_spectral_config(struct ath_hal *ah)
{
    u_int32_t val;
    struct ath_hal_9300 *ahp = AH9300(ah);
    HAL_BOOL asleep = ahp->ah_chip_full_sleep;

    if ((AR_SREV_WASP(ah) || AR_SREV_SCORPION(ah)) && asleep) {
        ar9300_set_power_mode(ah, HAL_PM_AWAKE, AH_TRUE);
    }

    val = OS_REG_READ(ah, AR_PHY_SPECTRAL_SCAN);

    if ((AR_SREV_WASP(ah) || AR_SREV_SCORPION(ah)) && asleep) {
        ar9300_set_power_mode(ah, HAL_PM_FULL_SLEEP, AH_TRUE);
    }
    return val;
}