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
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bt_intval; int /*<<< orphan*/  bt_nextatim; int /*<<< orphan*/  bt_nextswba; int /*<<< orphan*/  bt_nextdba; int /*<<< orphan*/  bt_nexttbtt; } ;
typedef  TYPE_1__ HAL_BEACON_TIMERS ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BEACON ; 
 int /*<<< orphan*/  AR_TIMER0 ; 
 int /*<<< orphan*/  AR_TIMER1 ; 
 int /*<<< orphan*/  AR_TIMER2 ; 
 int /*<<< orphan*/  AR_TIMER3 ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar5210SetBeaconTimers(struct ath_hal *ah, const HAL_BEACON_TIMERS *bt)
{

	OS_REG_WRITE(ah, AR_TIMER0, bt->bt_nexttbtt);
	OS_REG_WRITE(ah, AR_TIMER1, bt->bt_nextdba);
	OS_REG_WRITE(ah, AR_TIMER2, bt->bt_nextswba);
	OS_REG_WRITE(ah, AR_TIMER3, bt->bt_nextatim);
	/*
	 * Set the Beacon register after setting all timers.
	 */
	OS_REG_WRITE(ah, AR_BEACON, bt->bt_intval);
}