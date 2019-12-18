#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ v_type; int /*<<< orphan*/  v_mount; } ;
typedef  TYPE_1__ vnode_t ;
struct vattr {int va_mode; scalar_t__ va_uid; int /*<<< orphan*/  va_gid; } ;
struct TYPE_10__ {scalar_t__ cr_uid; } ;
typedef  TYPE_2__ cred_t ;

/* Variables and functions */
 int EFTYPE ; 
 int /*<<< orphan*/  PRIV_VFS_ADMIN ; 
 int /*<<< orphan*/  PRIV_VFS_STICKYFILE ; 
 int S_ISGID ; 
 int S_ISTXT ; 
 int S_ISUID ; 
 scalar_t__ VDIR ; 
 int priv_check_cred (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ secpolicy_fs_owner (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int secpolicy_vnode_setids_setgids (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

int
secpolicy_setid_setsticky_clear(vnode_t *vp, struct vattr *vap,
    const struct vattr *ovap, cred_t *cr)
{
        int error;

	if (secpolicy_fs_owner(vp->v_mount, cr) == 0)
		return (0);

	/*
	 * Privileged processes may set the sticky bit on non-directories,
	 * as well as set the setgid bit on a file with a group that the process
	 * is not a member of. Both of these are allowed in jail(8).
	 */
	if (vp->v_type != VDIR && (vap->va_mode & S_ISTXT)) {
		if (priv_check_cred(cr, PRIV_VFS_STICKYFILE))
			return (EFTYPE);
	}
	/*
	 * Check for privilege if attempting to set the
	 * group-id bit.
	 */
	if ((vap->va_mode & S_ISGID) != 0) {
		error = secpolicy_vnode_setids_setgids(vp, cr, ovap->va_gid);
		if (error)
			return (error);
	}
	/*
	 * Deny setting setuid if we are not the file owner.
	 */
	if ((vap->va_mode & S_ISUID) && ovap->va_uid != cr->cr_uid) {
		error = priv_check_cred(cr, PRIV_VFS_ADMIN);
		if (error)
			return (error);
	}
	return (0);
}