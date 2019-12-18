#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int z_pflags; TYPE_2__* z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_9__ {scalar_t__ z_replay; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {scalar_t__ v_type; } ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EPERM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VDIR ; 
 int WRITE_MASK_DATA ; 
 int ZFS_READONLY ; 
 TYPE_6__* ZTOV (TYPE_1__*) ; 
 int zfs_zaccess_aces_check (TYPE_1__*,int*,scalar_t__,int /*<<< orphan*/ *) ; 
 int zfs_zaccess_dataset_check (TYPE_1__*,int) ; 

__attribute__((used)) static int
zfs_zaccess_common(znode_t *zp, uint32_t v4_mode, uint32_t *working_mode,
    boolean_t *check_privs, boolean_t skipaclchk, cred_t *cr)
{
	zfsvfs_t *zfsvfs = zp->z_zfsvfs;
	int err;

	*working_mode = v4_mode;
	*check_privs = B_TRUE;

	/*
	 * Short circuit empty requests
	 */
	if (v4_mode == 0 || zfsvfs->z_replay) {
		*working_mode = 0;
		return (0);
	}

	if ((err = zfs_zaccess_dataset_check(zp, v4_mode)) != 0) {
		*check_privs = B_FALSE;
		return (err);
	}

	/*
	 * The caller requested that the ACL check be skipped.  This
	 * would only happen if the caller checked VOP_ACCESS() with a
	 * 32 bit ACE mask and already had the appropriate permissions.
	 */
	if (skipaclchk) {
		*working_mode = 0;
		return (0);
	}

	/*
	 * Note: ZFS_READONLY represents the "DOS R/O" attribute.
	 * When that flag is set, we should behave as if write access
	 * were not granted by anything in the ACL.  In particular:
	 * We _must_ allow writes after opening the file r/w, then
	 * setting the DOS R/O attribute, and writing some more.
	 * (Similar to how you can write after fchmod(fd, 0444).)
	 *
	 * Therefore ZFS_READONLY is ignored in the dataset check
	 * above, and checked here as if part of the ACL check.
	 * Also note: DOS R/O is ignored for directories.
	 */
	if ((v4_mode & WRITE_MASK_DATA) &&
	    (ZTOV(zp)->v_type != VDIR) &&
	    (zp->z_pflags & ZFS_READONLY)) {
		return (SET_ERROR(EPERM));
	}

	return (zfs_zaccess_aces_check(zp, working_mode, B_FALSE, cr));
}