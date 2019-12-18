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
struct vnode {scalar_t__ v_type; } ;
struct thread {int dummy; } ;
struct file {struct vnode* f_vnode; } ;

/* Variables and functions */
 int ENOTDIR ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  cap_read_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getvnode (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 

__attribute__((used)) static int
linux_getdents_error(struct thread *td, int fd, int err)
{
	struct vnode *vp;
	struct file *fp;
	int error;

	/* Linux return ENOTDIR in case when fd is not a directory. */
	error = getvnode(td, fd, &cap_read_rights, &fp);
	if (error != 0)
		return (error);
	vp = fp->f_vnode;
	if (vp->v_type != VDIR) {
		fdrop(fp, td);
		return (ENOTDIR);
	}
	fdrop(fp, td);
	return (err);
}