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
struct TYPE_3__ {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  interval; int /*<<< orphan*/  timer; int /*<<< orphan*/  pending; } ;
typedef  TYPE_1__ isc_ratelimiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SHUTTINGDOWN ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
#define  isc_ratelimiter_idle 131 
#define  isc_ratelimiter_ratelimited 130 
#define  isc_ratelimiter_shuttingdown 129 
#define  isc_ratelimiter_stalled 128 
 int /*<<< orphan*/  isc_timer_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_timertype_ticker ; 

isc_result_t
isc_ratelimiter_release(isc_ratelimiter_t *rl) {
	isc_result_t result = ISC_R_SUCCESS;

	LOCK(&rl->lock);
	switch (rl->state) {
	case isc_ratelimiter_shuttingdown:
		result = ISC_R_SHUTTINGDOWN;
		break;
	case isc_ratelimiter_stalled:
		if (!ISC_LIST_EMPTY(rl->pending)) {
			result = isc_timer_reset(rl->timer,
						 isc_timertype_ticker, NULL,
						 &rl->interval, ISC_FALSE);
			if (result == ISC_R_SUCCESS)
				rl->state = isc_ratelimiter_ratelimited;
		} else 
			rl->state = isc_ratelimiter_idle;
		break;
	case isc_ratelimiter_ratelimited:
	case isc_ratelimiter_idle:
		break;
	}
	UNLOCK(&rl->lock);
	return (result);
}