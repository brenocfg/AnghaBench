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
struct thread {int dummy; } ;
struct file {int /*<<< orphan*/  f_vnode; } ;
struct fchflags_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_FFLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (int /*<<< orphan*/ ) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_fchflags_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getvnode (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int setfflags (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 

int
sys_fchflags(struct thread *td, struct fchflags_args *uap)
{
	struct file *fp;
	int error;

	AUDIT_ARG_FD(uap->fd);
	AUDIT_ARG_FFLAGS(uap->flags);
	error = getvnode(td, uap->fd, &cap_fchflags_rights,
	    &fp);
	if (error != 0)
		return (error);
#ifdef AUDIT
	vn_lock(fp->f_vnode, LK_SHARED | LK_RETRY);
	AUDIT_ARG_VNODE1(fp->f_vnode);
	VOP_UNLOCK(fp->f_vnode, 0);
#endif
	error = setfflags(td, fp->f_vnode, uap->flags);
	fdrop(fp, td);
	return (error);
}