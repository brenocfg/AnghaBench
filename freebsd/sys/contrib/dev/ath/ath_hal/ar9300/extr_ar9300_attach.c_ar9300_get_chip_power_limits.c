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
struct ieee80211_channel {scalar_t__ ic_minpower; int /*<<< orphan*/  ic_maxpower; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR9300_MAX_RATE_POWER ; 

__attribute__((used)) static HAL_BOOL
ar9300_get_chip_power_limits(struct ath_hal *ah,
    struct ieee80211_channel *chan)
{

	chan->ic_maxpower = AR9300_MAX_RATE_POWER;
	chan->ic_minpower = 0;

	return AH_TRUE;
}