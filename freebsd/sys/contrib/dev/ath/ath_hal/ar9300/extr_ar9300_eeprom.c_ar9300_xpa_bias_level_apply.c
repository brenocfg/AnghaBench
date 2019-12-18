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
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AR_HORNET_CH0_TOP2 ; 
 int /*<<< orphan*/  AR_HORNET_CH0_TOP2_XPABIASLVL ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_THERM ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_THERM_XPABIASLVL_MSB ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_THERM_XPASHORT2GND ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_TOP ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_TOP_JUPITER ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_TOP_XPABIASLVL ; 
 int /*<<< orphan*/  AR_SCORPION_CH0_TOP ; 
 int /*<<< orphan*/  AR_SCORPION_CH0_TOP_XPABIASLVL ; 
 scalar_t__ AR_SREV_APHRODITE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_HORNET (struct ath_hal*) ; 
 scalar_t__ AR_SREV_JUPITER (struct ath_hal*) ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ar9300_xpa_bias_level_get (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL ar9300_xpa_bias_level_apply(struct ath_hal *ah, HAL_BOOL is_2ghz)
{
    /*
     * In ar9330 emu, we can't access radio registers, 
     * merlin is used for radio part.
     */
    int bias;
    bias = ar9300_xpa_bias_level_get(ah, is_2ghz);

    if (AR_SREV_HORNET(ah) || AR_SREV_POSEIDON(ah) || AR_SREV_WASP(ah)) {
        OS_REG_RMW_FIELD(ah,
            AR_HORNET_CH0_TOP2, AR_HORNET_CH0_TOP2_XPABIASLVL, bias);
    } else if (AR_SREV_SCORPION(ah)) {
        OS_REG_RMW_FIELD(ah,
            AR_SCORPION_CH0_TOP, AR_SCORPION_CH0_TOP_XPABIASLVL, bias);
    } else if (AR_SREV_JUPITER(ah) || AR_SREV_APHRODITE(ah)) {
        OS_REG_RMW_FIELD(ah,
            AR_PHY_65NM_CH0_TOP_JUPITER, AR_PHY_65NM_CH0_TOP_XPABIASLVL, bias);
    } else {
        OS_REG_RMW_FIELD(ah,
            AR_PHY_65NM_CH0_TOP, AR_PHY_65NM_CH0_TOP_XPABIASLVL, bias);
        OS_REG_RMW_FIELD(ah,
            AR_PHY_65NM_CH0_THERM, AR_PHY_65NM_CH0_THERM_XPABIASLVL_MSB,
            bias >> 2);
        OS_REG_RMW_FIELD(ah,
            AR_PHY_65NM_CH0_THERM, AR_PHY_65NM_CH0_THERM_XPASHORT2GND, 1);
    }
    return 0;
}