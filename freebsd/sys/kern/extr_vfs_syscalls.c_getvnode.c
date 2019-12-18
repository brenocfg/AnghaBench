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
struct thread {TYPE_1__* td_proc; } ;
struct file {int /*<<< orphan*/ * f_ops; int /*<<< orphan*/ * f_vnode; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  badfileops ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget_unlocked (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *) ; 

int
getvnode(struct thread *td, int fd, cap_rights_t *rightsp, struct file **fpp)
{
	struct file *fp;
	int error;

	error = fget_unlocked(td->td_proc->p_fd, fd, rightsp, &fp, NULL);
	if (error != 0)
		return (error);

	/*
	 * The file could be not of the vnode type, or it may be not
	 * yet fully initialized, in which case the f_vnode pointer
	 * may be set, but f_ops is still badfileops.  E.g.,
	 * devfs_open() transiently create such situation to
	 * facilitate csw d_fdopen().
	 *
	 * Dupfdopen() handling in kern_openat() installs the
	 * half-baked file into the process descriptor table, allowing
	 * other thread to dereference it. Guard against the race by
	 * checking f_ops.
	 */
	if (fp->f_vnode == NULL || fp->f_ops == &badfileops) {
		fdrop(fp, td);
		return (EINVAL);
	}
	*fpp = fp;
	return (0);
}