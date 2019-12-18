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
typedef  int /*<<< orphan*/  callb_cpr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALLB_CPR_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  callb_generic_cpr ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
txg_thread_enter(tx_state_t *tx, callb_cpr_t *cpr)
{
	CALLB_CPR_INIT(cpr, &tx->tx_sync_lock, callb_generic_cpr, FTAG);
	mutex_enter(&tx->tx_sync_lock);
}