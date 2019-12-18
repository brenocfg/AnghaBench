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
struct TYPE_3__ {int /*<<< orphan*/  tx_sync_lock; } ;
typedef  TYPE_1__ tx_state_t ;
typedef  int /*<<< orphan*/  kcondvar_t ;
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  callb_cpr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALLB_CPR_SAFE_BEGIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALLB_CPR_SAFE_END (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
txg_thread_wait(tx_state_t *tx, callb_cpr_t *cpr, kcondvar_t *cv, clock_t time)
{
	CALLB_CPR_SAFE_BEGIN(cpr);

	if (time)
		(void) cv_timedwait(cv, &tx->tx_sync_lock, time);
	else
		cv_wait(cv, &tx->tx_sync_lock);

	CALLB_CPR_SAFE_END(cpr, &tx->tx_sync_lock);
}