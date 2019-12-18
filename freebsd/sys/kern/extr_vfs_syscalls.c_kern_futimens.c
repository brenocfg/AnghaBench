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
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct file {int /*<<< orphan*/  f_vnode; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (int /*<<< orphan*/ ) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int UTIMENS_EXIT ; 
 int UTIMENS_NULL ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_futimes_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getutimens (struct timespec*,int,struct timespec*,int*) ; 
 int getvnode (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int setutimes (struct thread*,int /*<<< orphan*/ ,struct timespec*,int,int) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 

int
kern_futimens(struct thread *td, int fd, struct timespec *tptr,
    enum uio_seg tptrseg)
{
	struct timespec ts[2];
	struct file *fp;
	int error, flags;

	AUDIT_ARG_FD(fd);
	error = getutimens(tptr, tptrseg, ts, &flags);
	if (error != 0)
		return (error);
	if (flags & UTIMENS_EXIT)
		return (0);
	error = getvnode(td, fd, &cap_futimes_rights, &fp);
	if (error != 0)
		return (error);
#ifdef AUDIT
	vn_lock(fp->f_vnode, LK_SHARED | LK_RETRY);
	AUDIT_ARG_VNODE1(fp->f_vnode);
	VOP_UNLOCK(fp->f_vnode, 0);
#endif
	error = setutimes(td, fp->f_vnode, ts, 2, flags & UTIMENS_NULL);
	fdrop(fp, td);
	return (error);
}