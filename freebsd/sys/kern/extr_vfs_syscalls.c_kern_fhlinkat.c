#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  fh_fid; int /*<<< orphan*/  fh_fsid; } ;
typedef  TYPE_1__ fhandle_t ;
typedef  int /*<<< orphan*/  fh ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int EAGAIN ; 
 int ESTALE ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int /*<<< orphan*/  PRIV_VFS_GETFH ; 
 int VFS_FHTOVP (struct mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwillwrite () ; 
 int copyin (TYPE_1__*,TYPE_1__*,int) ; 
 int kern_linkat_vp (struct thread*,struct vnode*,int,char const*,int) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 struct mount* vfs_busyfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 

__attribute__((used)) static int
kern_fhlinkat(struct thread *td, int fd, const char *path,
    enum uio_seg pathseg, fhandle_t *fhp)
{
	fhandle_t fh;
	struct mount *mp;
	struct vnode *vp;
	int error;

	error = priv_check(td, PRIV_VFS_GETFH);
	if (error != 0)
		return (error);
	error = copyin(fhp, &fh, sizeof(fh));
	if (error != 0)
		return (error);
	do {
		bwillwrite();
		if ((mp = vfs_busyfs(&fh.fh_fsid)) == NULL)
			return (ESTALE);
		error = VFS_FHTOVP(mp, &fh.fh_fid, LK_SHARED, &vp);
		vfs_unbusy(mp);
		if (error != 0)
			return (error);
		VOP_UNLOCK(vp, 0);
	} while ((error = kern_linkat_vp(td, vp, fd, path, pathseg)) == EAGAIN);
	return (error);
}