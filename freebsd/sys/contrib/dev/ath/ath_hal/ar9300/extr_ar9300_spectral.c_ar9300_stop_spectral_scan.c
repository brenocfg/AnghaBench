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
typedef  int u_int32_t ;
struct ath_hal_9300 {int /*<<< orphan*/  ah_disable_cck; int /*<<< orphan*/  ah_dc_offset; int /*<<< orphan*/  ah_radar1; scalar_t__ ah_chip_full_sleep; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {scalar_t__ ah_curchan; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_PHY_ERR ; 
 int /*<<< orphan*/  AR_PHY_ERR_MASK_REG ; 
 int AR_PHY_ERR_RADAR ; 
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int /*<<< orphan*/  AR_PHY_MODE_DISABLE_CCK ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_CF_BIN_THRESH ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN ; 
 int AR_PHY_SPECTRAL_SCAN_ACTIVE ; 
 int /*<<< orphan*/  AR_PHY_TIMING2 ; 
 int /*<<< orphan*/  AR_PHY_TIMING2_DC_OFFSET ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  HAL_PM_FULL_SLEEP ; 
 scalar_t__ IS_5GHZ_FAST_CLOCK_EN (struct ath_hal*,scalar_t__) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9300_set_power_mode (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9300_stop_spectral_scan(struct ath_hal *ah)
{
    u_int32_t val;
    struct ath_hal_9300 *ahp = AH9300(ah);
    HAL_BOOL asleep = ahp->ah_chip_full_sleep;

    if ((AR_SREV_WASP(ah) || AR_SREV_SCORPION(ah)) && asleep) {
        ar9300_set_power_mode(ah, HAL_PM_AWAKE, AH_TRUE);
    }
    val = OS_REG_READ(ah, AR_PHY_SPECTRAL_SCAN);

    /* deactivate spectral scan */
    /* HW Bug fix -- Do not disable the spectral scan
     * only turn off the active bit
     */
    //val &= ~AR_PHY_SPECTRAL_SCAN_ENABLE;
    val &= ~AR_PHY_SPECTRAL_SCAN_ACTIVE;
    OS_REG_WRITE(ah, AR_PHY_SPECTRAL_SCAN, val);
    val = OS_REG_READ(ah, AR_PHY_SPECTRAL_SCAN);

    OS_REG_RMW_FIELD(ah, AR_PHY_RADAR_1, AR_PHY_RADAR_1_CF_BIN_THRESH,
                     ahp->ah_radar1);
    OS_REG_RMW_FIELD(ah, AR_PHY_TIMING2, AR_PHY_TIMING2_DC_OFFSET,
                     ahp->ah_dc_offset);
    OS_REG_WRITE(ah, AR_PHY_ERR, 0);

    if (AH_PRIVATE(ah)->ah_curchan &&
        IS_5GHZ_FAST_CLOCK_EN(ah, AH_PRIVATE(ah)->ah_curchan))
    { /* fast clock */
        OS_REG_RMW_FIELD(ah, AR_PHY_MODE, AR_PHY_MODE_DISABLE_CCK,
                         ahp->ah_disable_cck);
    }

    val = OS_REG_READ(ah, AR_PHY_ERR);
    
    val = OS_REG_READ(ah, AR_PHY_ERR_MASK_REG) & (~AR_PHY_ERR_RADAR);
    OS_REG_WRITE(ah, AR_PHY_ERR_MASK_REG, val);
    
    if ((AR_SREV_WASP(ah) || AR_SREV_SCORPION(ah)) && asleep) {
        ar9300_set_power_mode(ah, HAL_PM_FULL_SLEEP, AH_TRUE);
    }
}