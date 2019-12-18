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
struct vnode {int dummy; } ;
struct thread {TYPE_1__* td_proc; } ;
struct filedesc {int fd_nfiles; TYPE_2__* fd_ofiles; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct file* fde_file; } ;
struct TYPE_3__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 

__attribute__((used)) static int
fp_getfvp(struct thread *p, int fd, struct file **fpp, struct vnode **vpp)
{
	struct filedesc *fdp;
	struct file *fp;
	int error = 0;

	fdp = p->td_proc->p_fd;
	if (fd < 0 || fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[fd].fde_file) == NULL) {
		error = EBADF;
		goto out;
	}
	*fpp = fp;

out:
	NFSEXITCODE(error);
	return (error);
}