#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_8__ {int /*<<< orphan*/  ddlrta_txg; TYPE_2__* ddulrta_dd; } ;
typedef  TYPE_3__ ddulrt_arg_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dsl_dir_update_last_remap_txg_sync ; 
 int dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (int /*<<< orphan*/ ) ; 

int
dsl_dir_update_last_remap_txg(dsl_dir_t *dd, uint64_t txg)
{
	ddulrt_arg_t arg;
	arg.ddulrta_dd = dd;
	arg.ddlrta_txg = txg;

	return (dsl_sync_task(spa_name(dd->dd_pool->dp_spa),
	    NULL, dsl_dir_update_last_remap_txg_sync, &arg,
	    1, ZFS_SPACE_CHECK_RESERVED));
}