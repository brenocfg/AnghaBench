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
struct TYPE_7__ {scalar_t__ ah_opmode; } ;
struct TYPE_6__ {int bt_nexttbtt; int bt_nextdba; int bt_nextswba; int bt_nextatim; int bt_intval; } ;
typedef  TYPE_2__ HAL_BEACON_TIMERS ;

/* Variables and functions */
 TYPE_4__* AH_PRIVATE (struct ath_hal*) ; 
 int AR_BEACON_EN ; 
 int AR_BEACON_PERIOD ; 
 int AR_BEACON_RESET_TSF ; 
 scalar_t__ HAL_M_STA ; 
 int /*<<< orphan*/  ar5210SetBeaconTimers (struct ath_hal*,TYPE_2__*) ; 

void
ar5210BeaconInit(struct ath_hal *ah,
	uint32_t next_beacon, uint32_t beacon_period)
{
	HAL_BEACON_TIMERS bt;

	bt.bt_nexttbtt = next_beacon;

	if (AH_PRIVATE(ah)->ah_opmode != HAL_M_STA) {
		bt.bt_nextdba = (next_beacon -
			ah->ah_config.ah_dma_beacon_response_time) << 3; /* 1/8 TU */
		bt.bt_nextswba = (next_beacon -
            ah->ah_config.ah_sw_beacon_response_time) << 3;	/* 1/8 TU */
		/*
		 * The SWBA interrupt is not used for beacons in ad hoc mode
		 * as we don't yet support ATIMs. So since the beacon never
		 * changes, the beacon descriptor is set up once and read
		 * into a special HW buffer, from which it will be
		 * automagically retrieved at each DMA Beacon Alert (DBA).
		 */

		/* Set the ATIM window */
		bt.bt_nextatim = next_beacon + 0;	/* NB: no ATIMs */
	} else {
		bt.bt_nextdba = ~0;
		bt.bt_nextswba = ~0;
		bt.bt_nextatim = 1;
	}
	bt.bt_intval = beacon_period &
		(AR_BEACON_PERIOD | AR_BEACON_RESET_TSF | AR_BEACON_EN);
	ar5210SetBeaconTimers(ah, &bt);
}