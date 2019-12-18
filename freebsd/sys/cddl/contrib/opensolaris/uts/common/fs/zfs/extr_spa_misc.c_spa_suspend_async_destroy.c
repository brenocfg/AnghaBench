#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_root_dir; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {scalar_t__ dd_used_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_EXTRA_RESERVED ; 
 TYPE_4__* dsl_dir_phys (int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_pool_unreserved_space (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* spa_get_dsl (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_has_checkpoint (int /*<<< orphan*/ *) ; 

boolean_t
spa_suspend_async_destroy(spa_t *spa)
{
	dsl_pool_t *dp = spa_get_dsl(spa);

	uint64_t unreserved = dsl_pool_unreserved_space(dp,
	    ZFS_SPACE_CHECK_EXTRA_RESERVED);
	uint64_t used = dsl_dir_phys(dp->dp_root_dir)->dd_used_bytes;
	uint64_t avail = (unreserved > used) ? (unreserved - used) : 0;

	if (spa_has_checkpoint(spa) && avail == 0)
		return (B_TRUE);

	return (B_FALSE);
}