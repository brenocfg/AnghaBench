#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tx_threads; int /*<<< orphan*/  tx_sync_lock; void* tx_sync_thread; void* tx_quiesce_thread; } ;
typedef  TYPE_1__ tx_state_t ;
struct TYPE_7__ {int /*<<< orphan*/  dp_spa; TYPE_1__ dp_tx; } ;
typedef  TYPE_2__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  TS_RUN ; 
 int /*<<< orphan*/  dprintf (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  minclsyspri ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_proc (int /*<<< orphan*/ ) ; 
 void* thread_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_quiesce_thread ; 
 int /*<<< orphan*/  txg_sync_thread ; 

void
txg_sync_start(dsl_pool_t *dp)
{
	tx_state_t *tx = &dp->dp_tx;

	mutex_enter(&tx->tx_sync_lock);

	dprintf("pool %p\n", dp);

	ASSERT0(tx->tx_threads);

	tx->tx_threads = 2;

	tx->tx_quiesce_thread = thread_create(NULL, 0, txg_quiesce_thread,
	    dp, 0, spa_proc(dp->dp_spa), TS_RUN, minclsyspri);

	/*
	 * The sync thread can need a larger-than-default stack size on
	 * 32-bit x86.  This is due in part to nested pools and
	 * scrub_visitbp() recursion.
	 */
	tx->tx_sync_thread = thread_create(NULL, 32<<10, txg_sync_thread,
	    dp, 0, spa_proc(dp->dp_spa), TS_RUN, minclsyspri);

	mutex_exit(&tx->tx_sync_lock);
}