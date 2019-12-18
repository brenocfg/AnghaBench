#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_DELEG_PERM_DIFF ; 
 int zfs_secpolicy_destroy (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_hold (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_release (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_snapshot_perms (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_write_perms (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_secpolicy_tmp_snapshot(zfs_cmd_t *zc, nvlist_t *innvl, cred_t *cr)
{
	/*
	 * A temporary snapshot is the same as a snapshot,
	 * hold, destroy and release all rolled into one.
	 * Delegated diff alone is sufficient that we allow this.
	 */
	int error;

	if ((error = zfs_secpolicy_write_perms(zc->zc_name,
	    ZFS_DELEG_PERM_DIFF, cr)) == 0)
		return (0);

	error = zfs_secpolicy_snapshot_perms(zc->zc_name, cr);
	if (error == 0)
		error = zfs_secpolicy_hold(zc, innvl, cr);
	if (error == 0)
		error = zfs_secpolicy_release(zc, innvl, cr);
	if (error == 0)
		error = zfs_secpolicy_destroy(zc, innvl, cr);
	return (error);
}