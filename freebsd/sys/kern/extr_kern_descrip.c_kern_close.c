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
struct filedesc {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SYSCLOSE (struct thread*,int) ; 
 int EBADF ; 
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int closefp (struct filedesc*,int,struct file*,struct thread*,int) ; 
 int /*<<< orphan*/  fdfree (struct filedesc*,int) ; 
 struct file* fget_locked (struct filedesc*,int) ; 

int
kern_close(struct thread *td, int fd)
{
	struct filedesc *fdp;
	struct file *fp;

	fdp = td->td_proc->p_fd;

	AUDIT_SYSCLOSE(td, fd);

	FILEDESC_XLOCK(fdp);
	if ((fp = fget_locked(fdp, fd)) == NULL) {
		FILEDESC_XUNLOCK(fdp);
		return (EBADF);
	}
	fdfree(fdp, fd);

	/* closefp() drops the FILEDESC lock for us. */
	return (closefp(fdp, fd, fp, td, 1));
}