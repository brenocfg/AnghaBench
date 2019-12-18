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
struct thread {TYPE_2__* td_proc; } ;
struct filedesc {int fd_lastfile; TYPE_1__* fd_ofiles; } ;
struct closefrom_args {int lowfd; } ;
struct TYPE_4__ {struct filedesc* p_fd; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fde_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  kern_close (struct thread*,int) ; 

int
sys_closefrom(struct thread *td, struct closefrom_args *uap)
{
	struct filedesc *fdp;
	int fd;

	fdp = td->td_proc->p_fd;
	AUDIT_ARG_FD(uap->lowfd);

	/*
	 * Treat negative starting file descriptor values identical to
	 * closefrom(0) which closes all files.
	 */
	if (uap->lowfd < 0)
		uap->lowfd = 0;
	FILEDESC_SLOCK(fdp);
	for (fd = uap->lowfd; fd <= fdp->fd_lastfile; fd++) {
		if (fdp->fd_ofiles[fd].fde_file != NULL) {
			FILEDESC_SUNLOCK(fdp);
			(void)kern_close(td, fd);
			FILEDESC_SLOCK(fdp);
		}
	}
	FILEDESC_SUNLOCK(fdp);
	return (0);
}