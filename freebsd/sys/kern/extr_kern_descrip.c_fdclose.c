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
struct thread {TYPE_1__* td_proc; } ;
struct filedesc {TYPE_2__* fd_ofiles; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct file* fde_file; } ;
struct TYPE_3__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  fdfree (struct filedesc*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 

void
fdclose(struct thread *td, struct file *fp, int idx)
{
	struct filedesc *fdp = td->td_proc->p_fd;

	FILEDESC_XLOCK(fdp);
	if (fdp->fd_ofiles[idx].fde_file == fp) {
		fdfree(fdp, idx);
		FILEDESC_XUNLOCK(fdp);
		fdrop(fp, td);
	} else
		FILEDESC_XUNLOCK(fdp);
}