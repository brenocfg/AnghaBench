#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_space_check_t ;
typedef  int /*<<< orphan*/  dsl_syncfunc_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  dsl_sync_task_nowait_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dsl_sync_task_nowait(dsl_pool_t *dp, dsl_syncfunc_t *syncfunc, void *arg,
    int blocks_modified, zfs_space_check_t space_check, dmu_tx_t *tx)
{
	dsl_sync_task_nowait_common(dp, syncfunc, arg,
	    blocks_modified, space_check, tx, B_FALSE);
}