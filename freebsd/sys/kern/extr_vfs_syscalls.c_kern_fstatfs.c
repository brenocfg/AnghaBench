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
struct vnode {struct mount* v_mount; } ;
struct thread {int dummy; } ;
struct statfs {int dummy; } ;
struct mount {int dummy; } ;
struct file {struct vnode* f_vnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_fstatfs_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getvnode (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int kern_do_statfs (struct thread*,struct mount*,struct statfs*) ; 
 int /*<<< orphan*/  vfs_ref (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

int
kern_fstatfs(struct thread *td, int fd, struct statfs *buf)
{
	struct file *fp;
	struct mount *mp;
	struct vnode *vp;
	int error;

	AUDIT_ARG_FD(fd);
	error = getvnode(td, fd, &cap_fstatfs_rights, &fp);
	if (error != 0)
		return (error);
	vp = fp->f_vnode;
	vn_lock(vp, LK_SHARED | LK_RETRY);
#ifdef AUDIT
	AUDIT_ARG_VNODE1(vp);
#endif
	mp = vp->v_mount;
	if (mp != NULL)
		vfs_ref(mp);
	VOP_UNLOCK(vp, 0);
	fdrop(fp, td);
	return (kern_do_statfs(td, mp, buf));
}