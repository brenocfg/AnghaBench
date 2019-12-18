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
struct ath_hal_9300 {scalar_t__ ah_hw_green_tx_enable; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_TXRF3 ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_TXRF3_OLD_PAL_SPARE ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ar9300_hwgreentx_set_pal_spare(struct ath_hal *ah, int value)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    if (AR_SREV_POSEIDON(ah) && ahp->ah_hw_green_tx_enable) {
        if ((value == 0) || (value == 1)) {
            OS_REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_TXRF3, 
                             AR_PHY_65NM_CH0_TXRF3_OLD_PAL_SPARE, value);
        }
    }
}