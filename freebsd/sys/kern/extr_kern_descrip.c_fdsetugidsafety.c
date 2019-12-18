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
struct filedesc {int fd_refcnt; int fd_nfiles; TYPE_1__* fd_ofiles; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct filedesc* p_fd; } ;
struct TYPE_3__ {struct file* fde_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  closef (struct file*,struct thread*) ; 
 int /*<<< orphan*/  fdfree (struct filedesc*,int) ; 
 scalar_t__ is_unsafe (struct file*) ; 
 int /*<<< orphan*/  knote_fdclose (struct thread*,int) ; 

void
fdsetugidsafety(struct thread *td)
{
	struct filedesc *fdp;
	struct file *fp;
	int i;

	fdp = td->td_proc->p_fd;
	KASSERT(fdp->fd_refcnt == 1, ("the fdtable should not be shared"));
	MPASS(fdp->fd_nfiles >= 3);
	for (i = 0; i <= 2; i++) {
		fp = fdp->fd_ofiles[i].fde_file;
		if (fp != NULL && is_unsafe(fp)) {
			FILEDESC_XLOCK(fdp);
			knote_fdclose(td, i);
			/*
			 * NULL-out descriptor prior to close to avoid
			 * a race while close blocks.
			 */
			fdfree(fdp, i);
			FILEDESC_XUNLOCK(fdp);
			(void) closef(fp, td);
		}
	}
}