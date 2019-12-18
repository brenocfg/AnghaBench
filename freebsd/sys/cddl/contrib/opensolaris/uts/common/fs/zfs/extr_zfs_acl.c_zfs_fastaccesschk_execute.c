#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int z_pflags; scalar_t__ z_uid; scalar_t__ z_gid; int z_mode; int /*<<< orphan*/  z_zfsvfs; int /*<<< orphan*/  z_acl_lock; } ;
typedef  TYPE_1__ znode_t ;
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int boolean_t ;
struct TYPE_7__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_EXECUTE ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int /*<<< orphan*/  DTRACE_PROBE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EACCES ; 
 scalar_t__ FUID_INDEX (scalar_t__) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 scalar_t__ VDIR ; 
 int ZFS_AV_QUARANTINED ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ ) ; 
 int ZFS_NO_EXECS_DENIED ; 
 int ZFS_XATTR ; 
 TYPE_4__* ZTOV (TYPE_1__*) ; 
 scalar_t__ crgetuid (int /*<<< orphan*/ *) ; 
 scalar_t__ groupmember (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs__fastpath__execute__access__miss ; 
 int zfs_zaccess (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
zfs_fastaccesschk_execute(znode_t *zdp, cred_t *cr)
{
	boolean_t owner = B_FALSE;
	boolean_t groupmbr = B_FALSE;
	boolean_t is_attr;
	uid_t uid = crgetuid(cr);
	int error;

	if (zdp->z_pflags & ZFS_AV_QUARANTINED)
		return (SET_ERROR(EACCES));

	is_attr = ((zdp->z_pflags & ZFS_XATTR) &&
	    (ZTOV(zdp)->v_type == VDIR));
	if (is_attr)
		goto slow;


	mutex_enter(&zdp->z_acl_lock);

	if (zdp->z_pflags & ZFS_NO_EXECS_DENIED) {
		mutex_exit(&zdp->z_acl_lock);
		return (0);
	}

	if (FUID_INDEX(zdp->z_uid) != 0 || FUID_INDEX(zdp->z_gid) != 0) {
		mutex_exit(&zdp->z_acl_lock);
		goto slow;
	}

	if (uid == zdp->z_uid) {
		owner = B_TRUE;
		if (zdp->z_mode & S_IXUSR) {
			mutex_exit(&zdp->z_acl_lock);
			return (0);
		} else {
			mutex_exit(&zdp->z_acl_lock);
			goto slow;
		}
	}
	if (groupmember(zdp->z_gid, cr)) {
		groupmbr = B_TRUE;
		if (zdp->z_mode & S_IXGRP) {
			mutex_exit(&zdp->z_acl_lock);
			return (0);
		} else {
			mutex_exit(&zdp->z_acl_lock);
			goto slow;
		}
	}
	if (!owner && !groupmbr) {
		if (zdp->z_mode & S_IXOTH) {
			mutex_exit(&zdp->z_acl_lock);
			return (0);
		}
	}

	mutex_exit(&zdp->z_acl_lock);

slow:
	DTRACE_PROBE(zfs__fastpath__execute__access__miss);
	ZFS_ENTER(zdp->z_zfsvfs);
	error = zfs_zaccess(zdp, ACE_EXECUTE, 0, B_FALSE, cr);
	ZFS_EXIT(zdp->z_zfsvfs);
	return (error);
}