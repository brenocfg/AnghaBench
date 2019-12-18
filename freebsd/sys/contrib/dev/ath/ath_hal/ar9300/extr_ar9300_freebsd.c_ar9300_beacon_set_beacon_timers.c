#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_5__ {int ah_beaconInterval; } ;
struct TYPE_4__ {int bt_nexttbtt; int bt_nextatim; int bt_intval; scalar_t__ bt_flags; int /*<<< orphan*/  bt_nextswba; int /*<<< orphan*/  bt_nextdba; } ;
typedef  TYPE_1__ HAL_BEACON_TIMERS ;

/* Variables and functions */
 TYPE_3__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_BEACON_PERIOD ; 
 int AR_DBA_TIMER_EN ; 
 int /*<<< orphan*/  AR_DMA_BEACON_PERIOD ; 
 int /*<<< orphan*/  AR_NDP_PERIOD ; 
 int /*<<< orphan*/  AR_NEXT_DMA_BEACON_ALERT ; 
 int /*<<< orphan*/  AR_NEXT_NDP_TIMER ; 
 int /*<<< orphan*/  AR_NEXT_SWBA ; 
 int /*<<< orphan*/  AR_NEXT_TBTT_TIMER ; 
 int /*<<< orphan*/  AR_SWBA_PERIOD ; 
 int AR_SWBA_TIMER_EN ; 
 int AR_TBTT_TIMER_EN ; 
 int /*<<< orphan*/  AR_TIMER_MODE ; 
 int /*<<< orphan*/  AR_TXCFG ; 
 int AR_TXCFG_ADHOC_BEACON_ATIM_TX_POLICY ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int HAL_BEACON_PERIOD ; 
 int HAL_BEACON_RESET_TSF ; 
 scalar_t__ HAL_M_HOSTAP ; 
 scalar_t__ HAL_M_IBSS ; 
 int /*<<< orphan*/  ONE_EIGHTH_TU_TO_USEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TU_TO_USEC (int) ; 
 int /*<<< orphan*/  ar9300_reset_tsf (struct ath_hal*) ; 
 scalar_t__ opmode ; 

__attribute__((used)) static void
ar9300_beacon_set_beacon_timers(struct ath_hal *ah,
    const HAL_BEACON_TIMERS *bt)
{
	uint32_t bperiod;

#if 0
    HALASSERT(opmode == HAL_M_IBSS || opmode == HAL_M_HOSTAP);
    if (opmode == HAL_M_IBSS) {
        OS_REG_SET_BIT(ah, AR_TXCFG, AR_TXCFG_ADHOC_BEACON_ATIM_TX_POLICY);
    }
#endif

	/* XXX TODO: should migrate the HAL code to always use ONE_EIGHTH_TU */
	OS_REG_WRITE(ah, AR_NEXT_TBTT_TIMER, TU_TO_USEC(bt->bt_nexttbtt));
	OS_REG_WRITE(ah, AR_NEXT_DMA_BEACON_ALERT, ONE_EIGHTH_TU_TO_USEC(bt->bt_nextdba));
	OS_REG_WRITE(ah, AR_NEXT_SWBA, ONE_EIGHTH_TU_TO_USEC(bt->bt_nextswba));
	OS_REG_WRITE(ah, AR_NEXT_NDP_TIMER, TU_TO_USEC(bt->bt_nextatim));

	bperiod = TU_TO_USEC(bt->bt_intval & HAL_BEACON_PERIOD);
	AH9300(ah)->ah_beaconInterval = bt->bt_intval & HAL_BEACON_PERIOD;
	OS_REG_WRITE(ah, AR_BEACON_PERIOD, bperiod);
	OS_REG_WRITE(ah, AR_DMA_BEACON_PERIOD, bperiod);
	OS_REG_WRITE(ah, AR_SWBA_PERIOD, bperiod);
	OS_REG_WRITE(ah, AR_NDP_PERIOD, bperiod);

	/*
	 * Reset TSF if required.
	 */
	if (bt->bt_intval & HAL_BEACON_RESET_TSF)
		ar9300_reset_tsf(ah);

	/* enable timers */
	/* NB: flags == 0 handled specially for backwards compatibility */
	OS_REG_SET_BIT(ah, AR_TIMER_MODE,
	    bt->bt_flags != 0 ? bt->bt_flags :
	    AR_TBTT_TIMER_EN | AR_DBA_TIMER_EN | AR_SWBA_TIMER_EN);
}