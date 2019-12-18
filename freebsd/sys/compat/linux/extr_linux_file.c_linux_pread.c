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
struct linux_pread_args {int /*<<< orphan*/  fd; int /*<<< orphan*/  offset; int /*<<< orphan*/  nbyte; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int EISDIR ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  cap_pread_rights ; 
 int fgetvp (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vnode**) ; 
 int kern_pread (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
linux_pread(struct thread *td, struct linux_pread_args *uap)
{
	struct vnode *vp;
	int error;

	error = kern_pread(td, uap->fd, uap->buf, uap->nbyte, uap->offset);
	if (error == 0) {
		/* This seems to violate POSIX but Linux does it. */
		error = fgetvp(td, uap->fd, &cap_pread_rights, &vp);
		if (error != 0)
			return (error);
		if (vp->v_type == VDIR) {
			vrele(vp);
			return (EISDIR);
		}
		vrele(vp);
	}
	return (error);
}