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
struct ath_hal_5212 {int ah_beaconInterval; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int bt_nexttbtt; int bt_nextdba; int bt_nextswba; int bt_nextatim; int bt_intval; } ;
typedef  TYPE_1__ HAL_BEACON_TIMERS ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_BEACON ; 
 int AR_BEACON_RESET_TSF ; 
 int /*<<< orphan*/  AR_TIMER0 ; 
 int /*<<< orphan*/  AR_TIMER1 ; 
 int /*<<< orphan*/  AR_TIMER2 ; 
 int /*<<< orphan*/  AR_TIMER3 ; 
 int HAL_BEACON_PERIOD ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5212SetBeaconTimers(struct ath_hal *ah, const HAL_BEACON_TIMERS *bt)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	/*
	 * Limit the timers to their specific resolutions:
	 *
	 * + Timer 0 - 0..15 0xffff TU
	 * + Timer 1 - 0..18 0x7ffff TU/8
	 * + Timer 2 - 0..24 0x1ffffff TU/8
	 * + Timer 3 - 0..15 0xffff TU
	 */
	OS_REG_WRITE(ah, AR_TIMER0, bt->bt_nexttbtt & 0xffff);
	OS_REG_WRITE(ah, AR_TIMER1, bt->bt_nextdba & 0x7ffff);
	OS_REG_WRITE(ah, AR_TIMER2, bt->bt_nextswba & 0x1ffffff);
	/* XXX force nextatim to be non-zero? */
	OS_REG_WRITE(ah, AR_TIMER3, bt->bt_nextatim & 0xffff);
	/*
	 * Set the Beacon register after setting all timers.
	 */
	if (bt->bt_intval & AR_BEACON_RESET_TSF) {
		/*
		 * When resetting the TSF,
		 * write twice to the corresponding register; each
		 * write to the RESET_TSF bit toggles the internal
		 * signal to cause a reset of the TSF - but if the signal
		 * is left high, it will reset the TSF on the next
		 * chip reset also! writing the bit an even number
		 * of times fixes this issue
		 */
		OS_REG_WRITE(ah, AR_BEACON, AR_BEACON_RESET_TSF);
	}
	OS_REG_WRITE(ah, AR_BEACON, bt->bt_intval);
	ahp->ah_beaconInterval = (bt->bt_intval & HAL_BEACON_PERIOD);
}