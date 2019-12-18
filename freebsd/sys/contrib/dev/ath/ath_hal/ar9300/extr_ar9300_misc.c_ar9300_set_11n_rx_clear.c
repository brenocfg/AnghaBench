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
typedef  int HAL_HT_RXCLEAR ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DIAG_RX_CLEAR_CTL_LOW ; 
 int /*<<< orphan*/  AR_DIAG_RX_CLEAR_EXT_LOW ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int HAL_RX_CLEAR_CTL_LOW ; 
 int HAL_RX_CLEAR_EXT_LOW ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar9300_set_11n_rx_clear(struct ath_hal *ah, HAL_HT_RXCLEAR rxclear)
{
    /* control channel */
    if (rxclear & HAL_RX_CLEAR_CTL_LOW) {
        OS_REG_SET_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_CLEAR_CTL_LOW);
    } else {
        OS_REG_CLR_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_CLEAR_CTL_LOW);
    }
    /* extension channel */
    if (rxclear & HAL_RX_CLEAR_EXT_LOW) {
        OS_REG_SET_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_CLEAR_EXT_LOW);
    } else {
        OS_REG_CLR_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_CLEAR_EXT_LOW);
    }
}