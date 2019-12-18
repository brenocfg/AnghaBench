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
struct umask_args {int newmask; } ;
struct thread {int* td_retval; TYPE_1__* td_proc; } ;
struct filedesc {int fd_cmask; } ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int ALLPERMS ; 
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 

int
sys_umask(struct thread *td, struct umask_args *uap)
{
	struct filedesc *fdp;

	fdp = td->td_proc->p_fd;
	FILEDESC_XLOCK(fdp);
	td->td_retval[0] = fdp->fd_cmask;
	fdp->fd_cmask = uap->newmask & ALLPERMS;
	FILEDESC_XUNLOCK(fdp);
	return (0);
}