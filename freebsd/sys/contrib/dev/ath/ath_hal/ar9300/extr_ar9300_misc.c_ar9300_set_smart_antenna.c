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
struct ath_hal_9300 {int ah_smartantenna_enable; } ;
struct ath_hal {int dummy; } ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_ENABLE_SMARTANTENNA ; 
 int /*<<< orphan*/  AR_PHY_SWITCH_COM ; 
 int /*<<< orphan*/  AR_PHY_SWITCH_COM_2 ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_XRTO ; 
 int /*<<< orphan*/  HAL_CAP_SMARTANTENNA ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ar9300_get_capability (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_set_smart_antenna(struct ath_hal *ah, HAL_BOOL enable)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    if (enable) {
        OS_REG_SET_BIT(ah, AR_XRTO, AR_ENABLE_SMARTANTENNA);
    } else {
        OS_REG_CLR_BIT(ah, AR_XRTO, AR_ENABLE_SMARTANTENNA);
    }

    /* if scropion and smart antenna is enabled, write swcom1 with 0x440
     * and swcom2 with 0
     * FIXME Ideally these registers need to be made read from caldata.
     * Until the calibration team gets them, keep them along with board
     * configuration.
     */
    if (enable && AR_SREV_SCORPION(ah) &&
           (HAL_OK == ar9300_get_capability(ah, HAL_CAP_SMARTANTENNA, 0,0))) {

       OS_REG_WRITE(ah, AR_PHY_SWITCH_COM, 0x440);
       OS_REG_WRITE(ah, AR_PHY_SWITCH_COM_2, 0);
    }

    ahp->ah_smartantenna_enable = enable;
    return 1;
}