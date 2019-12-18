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
struct TYPE_3__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dsl_scan_cancel_check ; 
 int /*<<< orphan*/  dsl_scan_cancel_sync ; 
 int dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (int /*<<< orphan*/ ) ; 

int
dsl_scan_cancel(dsl_pool_t *dp)
{
	return (dsl_sync_task(spa_name(dp->dp_spa), dsl_scan_cancel_check,
	    dsl_scan_cancel_sync, NULL, 3, ZFS_SPACE_CHECK_RESERVED));
}