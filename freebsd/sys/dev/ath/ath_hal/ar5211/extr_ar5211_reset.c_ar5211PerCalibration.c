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
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  ar5211PerCalibrationN (struct ath_hal*,struct ieee80211_channel*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HAL_BOOL
ar5211PerCalibration(struct ath_hal *ah, struct ieee80211_channel *chan,
	HAL_BOOL *isIQdone)
{
	return ar5211PerCalibrationN(ah,  chan, 0x1, AH_TRUE, isIQdone);
}