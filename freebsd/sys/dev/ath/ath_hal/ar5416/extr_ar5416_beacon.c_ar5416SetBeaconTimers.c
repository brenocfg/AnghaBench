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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal_5212 {int ah_beaconInterval; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int bt_nexttbtt; int bt_nextatim; int bt_intval; scalar_t__ bt_flags; int /*<<< orphan*/  bt_nextswba; int /*<<< orphan*/  bt_nextdba; } ;
typedef  TYPE_1__ HAL_BEACON_TIMERS ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR5416_BEACON_PERIOD ; 
 int AR_BEACON_RESET_TSF ; 
 int /*<<< orphan*/  AR_DBA_PERIOD ; 
 int /*<<< orphan*/  AR_NDP_PERIOD ; 
 int /*<<< orphan*/  AR_NEXT_DBA ; 
 int /*<<< orphan*/  AR_NEXT_NDP ; 
 int /*<<< orphan*/  AR_NEXT_SWBA ; 
 int /*<<< orphan*/  AR_NEXT_TBTT ; 
 int /*<<< orphan*/  AR_SWBA_PERIOD ; 
 int /*<<< orphan*/  AR_TIMER_MODE ; 
 int AR_TIMER_MODE_DBA ; 
 int AR_TIMER_MODE_SWBA ; 
 int AR_TIMER_MODE_TBTT ; 
 int HAL_BEACON_PERIOD ; 
 int /*<<< orphan*/  ONE_EIGHTH_TU_TO_USEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TU_TO_USEC (int) ; 
 int /*<<< orphan*/  ar5416ResetTsf (struct ath_hal*) ; 

void
ar5416SetBeaconTimers(struct ath_hal *ah, const HAL_BEACON_TIMERS *bt)
{
	uint32_t bperiod;
	struct ath_hal_5212 *ahp = AH5212(ah);

	OS_REG_WRITE(ah, AR_NEXT_TBTT, TU_TO_USEC(bt->bt_nexttbtt));
	OS_REG_WRITE(ah, AR_NEXT_DBA, ONE_EIGHTH_TU_TO_USEC(bt->bt_nextdba));
	OS_REG_WRITE(ah, AR_NEXT_SWBA, ONE_EIGHTH_TU_TO_USEC(bt->bt_nextswba));
	OS_REG_WRITE(ah, AR_NEXT_NDP, TU_TO_USEC(bt->bt_nextatim));

	bperiod = TU_TO_USEC(bt->bt_intval & HAL_BEACON_PERIOD);
	ahp->ah_beaconInterval = bt->bt_intval & HAL_BEACON_PERIOD;
	OS_REG_WRITE(ah, AR5416_BEACON_PERIOD, bperiod);
	OS_REG_WRITE(ah, AR_DBA_PERIOD, bperiod);
	OS_REG_WRITE(ah, AR_SWBA_PERIOD, bperiod);
	OS_REG_WRITE(ah, AR_NDP_PERIOD, bperiod);

	/*
	 * Reset TSF if required.
	 */
	if (bt->bt_intval & AR_BEACON_RESET_TSF)
		ar5416ResetTsf(ah);

	/* enable timers */
	/* NB: flags == 0 handled specially for backwards compatibility */
	OS_REG_SET_BIT(ah, AR_TIMER_MODE,
	    bt->bt_flags != 0 ? bt->bt_flags :
		AR_TIMER_MODE_TBTT | AR_TIMER_MODE_DBA | AR_TIMER_MODE_SWBA);
}