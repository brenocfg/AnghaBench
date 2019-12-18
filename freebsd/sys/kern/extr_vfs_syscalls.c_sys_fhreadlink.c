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
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct fhreadlink_args {scalar_t__ bufsize; int /*<<< orphan*/  buf; int /*<<< orphan*/  fhp; } ;
struct TYPE_3__ {int /*<<< orphan*/  fh_fid; int /*<<< orphan*/  fh_fsid; } ;
typedef  TYPE_1__ fhandle_t ;
typedef  int /*<<< orphan*/  fh ;

/* Variables and functions */
 int EINVAL ; 
 int ESTALE ; 
 scalar_t__ IOSIZE_MAX ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int /*<<< orphan*/  PRIV_VFS_GETFH ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int VFS_FHTOVP (struct mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vnode**) ; 
 int copyin (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int kern_readlink_vp (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct thread*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 struct mount* vfs_busyfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
sys_fhreadlink(struct thread *td, struct fhreadlink_args *uap)
{
	fhandle_t fh;
	struct mount *mp;
	struct vnode *vp;
	int error;

	error = priv_check(td, PRIV_VFS_GETFH);
	if (error != 0)
		return (error);
	if (uap->bufsize > IOSIZE_MAX)
		return (EINVAL);
	error = copyin(uap->fhp, &fh, sizeof(fh));
	if (error != 0)
		return (error);
	if ((mp = vfs_busyfs(&fh.fh_fsid)) == NULL)
		return (ESTALE);
	error = VFS_FHTOVP(mp, &fh.fh_fid, LK_SHARED, &vp);
	vfs_unbusy(mp);
	if (error != 0)
		return (error);
	error = kern_readlink_vp(vp, uap->buf, UIO_USERSPACE, uap->bufsize, td);
	vput(vp);
	return (error);
}