#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_13__ {TYPE_1__* sm_phys; int /*<<< orphan*/  sm_os; int /*<<< orphan*/  sm_dbuf; } ;
typedef  TYPE_3__ space_map_t ;
typedef  int /*<<< orphan*/  maptype_t ;
struct TYPE_14__ {TYPE_2__* tx_pool; } ;
typedef  TYPE_4__ dmu_tx_t ;
typedef  int /*<<< orphan*/  dentry ;
struct TYPE_12__ {int /*<<< orphan*/  dp_spa; } ;
struct TYPE_11__ {int smp_objsize; } ;

/* Variables and functions */
 int SM_DEBUG_ACTION_ENCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_DEBUG_PREFIX ; 
 int SM_DEBUG_SYNCPASS_ENCODE (int /*<<< orphan*/ ) ; 
 int SM_DEBUG_TXG_ENCODE (int /*<<< orphan*/ ) ; 
 int SM_PREFIX_ENCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dmu_tx_get_txg (TYPE_4__*) ; 
 int /*<<< orphan*/  dmu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,TYPE_4__*) ; 
 int /*<<< orphan*/  spa_sync_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  space_map_object (TYPE_3__*) ; 

__attribute__((used)) static void
space_map_write_intro_debug(space_map_t *sm, maptype_t maptype, dmu_tx_t *tx)
{
	dmu_buf_will_dirty(sm->sm_dbuf, tx);

	uint64_t dentry = SM_PREFIX_ENCODE(SM_DEBUG_PREFIX) |
	    SM_DEBUG_ACTION_ENCODE(maptype) |
	    SM_DEBUG_SYNCPASS_ENCODE(spa_sync_pass(tx->tx_pool->dp_spa)) |
	    SM_DEBUG_TXG_ENCODE(dmu_tx_get_txg(tx));

	dmu_write(sm->sm_os, space_map_object(sm), sm->sm_phys->smp_objsize,
	    sizeof (dentry), &dentry, tx);

	sm->sm_phys->smp_objsize += sizeof (dentry);
}