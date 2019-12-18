#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ dp_dirty_total; int /*<<< orphan*/  dp_lock; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_kick (TYPE_1__*) ; 
 int zfs_delay_min_dirty_percent ; 
 int zfs_dirty_data_max ; 
 int zfs_dirty_data_sync_pct ; 

boolean_t
dsl_pool_need_dirty_delay(dsl_pool_t *dp)
{
	uint64_t delay_min_bytes =
	    zfs_dirty_data_max * zfs_delay_min_dirty_percent / 100;
	uint64_t dirty_min_bytes =
	    zfs_dirty_data_max * zfs_dirty_data_sync_pct / 100;
	boolean_t rv;

	mutex_enter(&dp->dp_lock);
	if (dp->dp_dirty_total > dirty_min_bytes)
		txg_kick(dp);
	rv = (dp->dp_dirty_total > delay_min_bytes);
	mutex_exit(&dp->dp_lock);
	return (rv);
}