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
struct vnode {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct statfs {int dummy; } ;
struct mount {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fh_fid; int /*<<< orphan*/  fh_fsid; } ;
typedef  TYPE_1__ fhandle_t ;

/* Variables and functions */
 int ESTALE ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  PRIV_VFS_FHSTATFS ; 
 int VFS_FHTOVP (struct mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vnode**) ; 
 int VFS_STATFS (struct mount*,struct statfs*) ; 
 int mac_mount_check_stat (int /*<<< orphan*/ ,struct mount*) ; 
 int prison_canseemount (int /*<<< orphan*/ ,struct mount*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 struct mount* vfs_busyfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
kern_fhstatfs(struct thread *td, fhandle_t fh, struct statfs *buf)
{
	struct mount *mp;
	struct vnode *vp;
	int error;

	error = priv_check(td, PRIV_VFS_FHSTATFS);
	if (error != 0)
		return (error);
	if ((mp = vfs_busyfs(&fh.fh_fsid)) == NULL)
		return (ESTALE);
	error = VFS_FHTOVP(mp, &fh.fh_fid, LK_EXCLUSIVE, &vp);
	if (error != 0) {
		vfs_unbusy(mp);
		return (error);
	}
	vput(vp);
	error = prison_canseemount(td->td_ucred, mp);
	if (error != 0)
		goto out;
#ifdef MAC
	error = mac_mount_check_stat(td->td_ucred, mp);
	if (error != 0)
		goto out;
#endif
	error = VFS_STATFS(mp, buf);
out:
	vfs_unbusy(mp);
	return (error);
}