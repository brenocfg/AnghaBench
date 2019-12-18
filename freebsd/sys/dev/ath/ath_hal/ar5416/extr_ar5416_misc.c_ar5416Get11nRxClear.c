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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_HT_RXCLEAR ;

/* Variables and functions */
 int AR_DIAG_RXCLEAR_CTL_LOW ; 
 int AR_DIAG_RXCLEAR_EXT_LOW ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  HAL_RX_CLEAR_CTL_LOW ; 
 int /*<<< orphan*/  HAL_RX_CLEAR_EXT_LOW ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_HT_RXCLEAR
ar5416Get11nRxClear(struct ath_hal *ah)
{
    HAL_HT_RXCLEAR rxclear = 0;
    uint32_t val;

    val = OS_REG_READ(ah, AR_DIAG_SW);

    /* control channel */
    if (val & AR_DIAG_RXCLEAR_CTL_LOW) {
        rxclear |= HAL_RX_CLEAR_CTL_LOW;
    }
    /* extension channel */
    if (val & AR_DIAG_RXCLEAR_EXT_LOW) {
        rxclear |= HAL_RX_CLEAR_EXT_LOW;
    }
    return rxclear;
}