#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int ah_dma_beacon_response_time; int ah_sw_beacon_response_time; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
struct TYPE_7__ {int ah_opmode; } ;
struct TYPE_6__ {int bt_nexttbtt; int bt_nextdba; int bt_nextswba; int bt_nextatim; int bt_intval; } ;
typedef  TYPE_2__ HAL_BEACON_TIMERS ;

/* Variables and functions */
 TYPE_4__* AH_PRIVATE (struct ath_hal*) ; 
 int AR_BEACON_EN ; 
 int AR_BEACON_PERIOD ; 
 int AR_BEACON_RESET_TSF ; 
#define  HAL_M_HOSTAP 131 
#define  HAL_M_IBSS 130 
#define  HAL_M_MONITOR 129 
#define  HAL_M_STA 128 
 int /*<<< orphan*/  ar5211SetBeaconTimers (struct ath_hal*,TYPE_2__*) ; 

void
ar5211BeaconInit(struct ath_hal *ah,
	uint32_t next_beacon, uint32_t beacon_period)
{
	HAL_BEACON_TIMERS bt;

	bt.bt_nexttbtt = next_beacon;
	/* 
	 * TIMER1: in AP/adhoc mode this controls the DMA beacon
	 * alert timer; otherwise it controls the next wakeup time.
	 * TIMER2: in AP mode, it controls the SBA beacon alert
	 * interrupt; otherwise it sets the start of the next CFP.
	 */
	switch (AH_PRIVATE(ah)->ah_opmode) {
	case HAL_M_STA:
	case HAL_M_MONITOR:
		bt.bt_nextdba = 0xffff;
		bt.bt_nextswba = 0x7ffff;
		break;
	case HAL_M_IBSS:
	case HAL_M_HOSTAP:
		bt.bt_nextdba = (next_beacon -
			ah->ah_config.ah_dma_beacon_response_time) << 3;	/* 1/8 TU */
		bt.bt_nextswba = (next_beacon -
            ah->ah_config.ah_sw_beacon_response_time) << 3;	/* 1/8 TU */
		break;
	}
	/*
	 * Set the ATIM window 
	 * Our hardware does not support an ATIM window of 0
	 * (beacons will not work).  If the ATIM windows is 0,
	 * force it to 1.
	 */
	bt.bt_nextatim = next_beacon + 1;
	bt.bt_intval = beacon_period &
		(AR_BEACON_PERIOD | AR_BEACON_RESET_TSF | AR_BEACON_EN);
	ar5211SetBeaconTimers(ah, &bt);
}