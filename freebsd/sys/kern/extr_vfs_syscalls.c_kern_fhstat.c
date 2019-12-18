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
struct vnode {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct stat {int dummy; } ;
struct mount {int dummy; } ;
struct fhandle {int /*<<< orphan*/  fh_fid; int /*<<< orphan*/  fh_fsid; } ;

/* Variables and functions */
 int ESTALE ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  PRIV_VFS_FHSTAT ; 
 int VFS_FHTOVP (struct mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vnode**) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 struct mount* vfs_busyfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int vn_stat (struct vnode*,struct stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
kern_fhstat(struct thread *td, struct fhandle fh, struct stat *sb)
{
	struct mount *mp;
	struct vnode *vp;
	int error;

	error = priv_check(td, PRIV_VFS_FHSTAT);
	if (error != 0)
		return (error);
	if ((mp = vfs_busyfs(&fh.fh_fsid)) == NULL)
		return (ESTALE);
	error = VFS_FHTOVP(mp, &fh.fh_fid, LK_EXCLUSIVE, &vp);
	vfs_unbusy(mp);
	if (error != 0)
		return (error);
	error = vn_stat(vp, sb, td->td_ucred, NOCRED, td);
	vput(vp);
	return (error);
}