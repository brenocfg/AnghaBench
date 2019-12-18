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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  spa_feature_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_activate_feature_check ; 
 int /*<<< orphan*/  zfs_prop_activate_feature_sync ; 

__attribute__((used)) static int
zfs_prop_activate_feature(spa_t *spa, spa_feature_t feature)
{
	int err;

	/* EBUSY here indicates that the feature is already active */
	err = dsl_sync_task(spa_name(spa),
	    zfs_prop_activate_feature_check, zfs_prop_activate_feature_sync,
	    &feature, 2, ZFS_SPACE_CHECK_RESERVED);

	if (err != 0 && err != EBUSY)
		return (err);
	else
		return (0);
}