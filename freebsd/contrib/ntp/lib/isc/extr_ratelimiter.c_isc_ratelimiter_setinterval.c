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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  interval; int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ isc_ratelimiter_t ;
typedef  int /*<<< orphan*/  isc_interval_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ isc_ratelimiter_ratelimited ; 
 int /*<<< orphan*/  isc_timer_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_timertype_ticker ; 

isc_result_t
isc_ratelimiter_setinterval(isc_ratelimiter_t *rl, isc_interval_t *interval) {
	isc_result_t result = ISC_R_SUCCESS;
	LOCK(&rl->lock);
	rl->interval = *interval;
	/*
	 * If the timer is currently running, change its rate.
	 */
        if (rl->state == isc_ratelimiter_ratelimited) {
		result = isc_timer_reset(rl->timer, isc_timertype_ticker, NULL,
					 &rl->interval, ISC_FALSE);
	}
	UNLOCK(&rl->lock);
	return (result);
}