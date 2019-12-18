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
struct TYPE_2__ {int /*<<< orphan*/  get_chip_power_lim; int /*<<< orphan*/  set_channel; } ;
struct ath_hal_9300 {TYPE_1__ ah_rf_hal; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  HAL_OK ; 
 int /*<<< orphan*/  ar9300_get_chip_power_limits ; 
 int /*<<< orphan*/  ar9300_set_channel ; 

HAL_BOOL
ar9300_rf_attach(struct ath_hal *ah, HAL_STATUS *status)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    ahp->ah_rf_hal.set_channel    = ar9300_set_channel;
    ahp->ah_rf_hal.get_chip_power_lim   = ar9300_get_chip_power_limits;

    *status = HAL_OK;

    return AH_TRUE;
}