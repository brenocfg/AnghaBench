#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uio {int dummy; } ;
struct thread {int dummy; } ;
struct file {TYPE_1__* f_vnode; TYPE_2__* f_ops; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {int fo_flags; } ;
struct TYPE_3__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int DFLAG_SEEKABLE ; 
 int EINVAL ; 
 int ESPIPE ; 
 int /*<<< orphan*/  FOF_OFFSET ; 
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  cap_pwrite_rights ; 
 int dofilewrite (struct thread*,int,struct file*,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget_write (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 

int
kern_pwritev(struct thread *td, int fd, struct uio *auio, off_t offset)
{
	struct file *fp;
	int error;

	error = fget_write(td, fd, &cap_pwrite_rights, &fp);
	if (error)
		return (error);
	if (!(fp->f_ops->fo_flags & DFLAG_SEEKABLE))
		error = ESPIPE;
	else if (offset < 0 &&
	    (fp->f_vnode == NULL || fp->f_vnode->v_type != VCHR))
		error = EINVAL;
	else
		error = dofilewrite(td, fd, fp, auio, offset, FOF_OFFSET);
	fdrop(fp, td);
	return (error);
}