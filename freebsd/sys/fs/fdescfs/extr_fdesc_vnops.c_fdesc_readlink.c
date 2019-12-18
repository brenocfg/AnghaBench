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
struct vop_readlink_args {struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_data; } ;
struct uio {int dummy; } ;
struct thread {int dummy; } ;
struct file {int f_type; struct vnode* f_vnode; } ;
struct fdescnode {int fd_fd; } ;
struct TYPE_2__ {scalar_t__ fd_type; } ;

/* Variables and functions */
#define  DTYPE_VNODE 128 
 scalar_t__ Fdesc ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  M_TEMP ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* VTOFDESC (struct vnode*) ; 
 int /*<<< orphan*/  cap_no_rights ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget_cap (struct thread*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 size_t strlen (char*) ; 
 int uiomove (char*,size_t,struct uio*) ; 
 int vn_fullpath (struct thread*,struct vnode*,char**,char**) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
fdesc_readlink(struct vop_readlink_args *va)
{
	struct vnode *vp, *vn;
	struct thread *td;
	struct uio *uio;
	struct file *fp;
	char *freepath, *fullpath;
	size_t pathlen;
	int lockflags, fd_fd;
	int error;

	freepath = NULL;
	vn = va->a_vp;
	if (VTOFDESC(vn)->fd_type != Fdesc)
		panic("fdesc_readlink: not fdescfs link");
	fd_fd = ((struct fdescnode *)vn->v_data)->fd_fd;
	lockflags = VOP_ISLOCKED(vn);
	VOP_UNLOCK(vn, 0);

	td = curthread;
	error = fget_cap(td, fd_fd, &cap_no_rights, &fp, NULL);
	if (error != 0)
		goto out;

	switch (fp->f_type) {
	case DTYPE_VNODE:
		vp = fp->f_vnode;
		error = vn_fullpath(td, vp, &fullpath, &freepath);
		break;
	default:
		fullpath = "anon_inode:[unknown]";
		break;
	}
	if (error == 0) {
		uio = va->a_uio;
		pathlen = strlen(fullpath);
		error = uiomove(fullpath, pathlen, uio);
	}
	if (freepath != NULL)
		free(freepath, M_TEMP);
	fdrop(fp, td);

out:
	vn_lock(vn, lockflags | LK_RETRY);
	return (error);
}