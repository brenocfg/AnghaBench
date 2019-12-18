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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_powerLimit; struct ieee80211_channel* ah_curchan; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  MAX_RATE_POWER ; 
 int /*<<< orphan*/  SAVE_CCK (struct ath_hal*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5212SetTransmitPower (struct ath_hal*,struct ieee80211_channel*,int /*<<< orphan*/ *) ; 

HAL_BOOL
ar5212SetTxPowerLimit(struct ath_hal *ah, uint32_t limit)
{
	/* XXX blech, construct local writable copy */
	struct ieee80211_channel dummy = *AH_PRIVATE(ah)->ah_curchan;
	uint16_t dummyXpdGains[2];
	HAL_BOOL isBmode;

	SAVE_CCK(ah, &dummy, isBmode);
	AH_PRIVATE(ah)->ah_powerLimit = AH_MIN(limit, MAX_RATE_POWER);
	return ar5212SetTransmitPower(ah, &dummy, dummyXpdGains);
}