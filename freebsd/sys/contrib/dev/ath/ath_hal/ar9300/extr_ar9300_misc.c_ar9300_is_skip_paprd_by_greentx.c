#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ath_hal_sta_update_tx_pwr_enable; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
struct TYPE_4__ {scalar_t__ green_tx_status; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 scalar_t__ HAL_RSSI_TX_POWER_MIDDLE ; 
 scalar_t__ HAL_RSSI_TX_POWER_SHORT ; 

HAL_BOOL
ar9300_is_skip_paprd_by_greentx(struct ath_hal *ah)
{
    if (AR_SREV_POSEIDON(ah) && 
        ah->ah_config.ath_hal_sta_update_tx_pwr_enable &&
        ((AH9300(ah)->green_tx_status == HAL_RSSI_TX_POWER_SHORT) || 
         (AH9300(ah)->green_tx_status == HAL_RSSI_TX_POWER_MIDDLE))) 
    {
        return AH_TRUE;
    }
    return AH_FALSE;
}