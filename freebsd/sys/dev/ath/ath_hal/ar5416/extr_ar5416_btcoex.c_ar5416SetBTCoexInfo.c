#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath_hal_5416 {int /*<<< orphan*/  ah_btWlanIsolation; int /*<<< orphan*/  ah_btCoexSingleAnt; int /*<<< orphan*/  ah_btActivePolarity; int /*<<< orphan*/  ah_wlanActiveGpioSelect; int /*<<< orphan*/  ah_btPriorityGpioSelect; int /*<<< orphan*/  ah_btActiveGpioSelect; int /*<<< orphan*/  ah_btCoexConfigType; int /*<<< orphan*/  ah_btModule; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bt_isolation; int /*<<< orphan*/  bt_single_ant; int /*<<< orphan*/  bt_active_polarity; int /*<<< orphan*/  bt_gpio_wlan_active; int /*<<< orphan*/  bt_gpio_bt_priority; int /*<<< orphan*/  bt_gpio_bt_active; int /*<<< orphan*/  bt_coex_config; int /*<<< orphan*/  bt_module; } ;
typedef  TYPE_1__ HAL_BT_COEX_INFO ;

/* Variables and functions */
 struct ath_hal_5416* AH5416 (struct ath_hal*) ; 

void
ar5416SetBTCoexInfo(struct ath_hal *ah, HAL_BT_COEX_INFO *btinfo)
{
	struct ath_hal_5416 *ahp = AH5416(ah);

	ahp->ah_btModule = btinfo->bt_module;
	ahp->ah_btCoexConfigType = btinfo->bt_coex_config;
	ahp->ah_btActiveGpioSelect = btinfo->bt_gpio_bt_active;
	ahp->ah_btPriorityGpioSelect = btinfo->bt_gpio_bt_priority;
	ahp->ah_wlanActiveGpioSelect = btinfo->bt_gpio_wlan_active;
	ahp->ah_btActivePolarity = btinfo->bt_active_polarity;
	ahp->ah_btCoexSingleAnt = btinfo->bt_single_ant;
	ahp->ah_btWlanIsolation = btinfo->bt_isolation;
}