#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct quotactl_args {int cmd; int /*<<< orphan*/  arg; int /*<<< orphan*/  uid; int /*<<< orphan*/  path; } ;
struct nameidata {TYPE_1__* ni_vp; } ;
struct mount {int dummy; } ;
struct TYPE_2__ {struct mount* v_mount; } ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG_CMD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_UID (int /*<<< orphan*/ ) ; 
 int EPERM ; 
 int FOLLOW ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  PR_ALLOW_QUOTAS ; 
 int Q_QUOTAOFF ; 
 int Q_QUOTAON ; 
 int SUBCMDSHIFT ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int VFS_QUOTACTL (struct mount*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  prison_allow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_ref (struct mount*) ; 
 int /*<<< orphan*/  vfs_rel (struct mount*) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vput (TYPE_1__*) ; 

int
sys_quotactl(struct thread *td, struct quotactl_args *uap)
{
	struct mount *mp;
	struct nameidata nd;
	int error;

	AUDIT_ARG_CMD(uap->cmd);
	AUDIT_ARG_UID(uap->uid);
	if (!prison_allow(td->td_ucred, PR_ALLOW_QUOTAS))
		return (EPERM);
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF | AUDITVNODE1, UIO_USERSPACE,
	    uap->path, td);
	if ((error = namei(&nd)) != 0)
		return (error);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	mp = nd.ni_vp->v_mount;
	vfs_ref(mp);
	vput(nd.ni_vp);
	error = vfs_busy(mp, 0);
	vfs_rel(mp);
	if (error != 0)
		return (error);
	error = VFS_QUOTACTL(mp, uap->cmd, uap->uid, uap->arg);

	/*
	 * Since quota on operation typically needs to open quota
	 * file, the Q_QUOTAON handler needs to unbusy the mount point
	 * before calling into namei.  Otherwise, unmount might be
	 * started between two vfs_busy() invocations (first is our,
	 * second is from mount point cross-walk code in lookup()),
	 * causing deadlock.
	 *
	 * Require that Q_QUOTAON handles the vfs_busy() reference on
	 * its own, always returning with ubusied mount point.
	 */
	if ((uap->cmd >> SUBCMDSHIFT) != Q_QUOTAON &&
	    (uap->cmd >> SUBCMDSHIFT) != Q_QUOTAOFF)
		vfs_unbusy(mp);
	return (error);
}