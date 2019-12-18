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
struct filedesc {scalar_t__ fd_holdleaderscount; scalar_t__ fd_holdleaderswakeup; int /*<<< orphan*/  fd_kqlist; } ;
struct file {scalar_t__ f_type; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p_fdtol; } ;

/* Variables and functions */
 scalar_t__ DTYPE_MQUEUE ; 
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XLOCK_ASSERT (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ __predict_false (int) ; 
 int closef (struct file*,struct thread*) ; 
 int /*<<< orphan*/  knote_fdclose (struct thread*,int) ; 
 int /*<<< orphan*/  mq_fdclose (struct thread*,int,struct file*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static int
closefp(struct filedesc *fdp, int fd, struct file *fp, struct thread *td,
    int holdleaders)
{
	int error;

	FILEDESC_XLOCK_ASSERT(fdp);

	if (holdleaders) {
		if (td->td_proc->p_fdtol != NULL) {
			/*
			 * Ask fdfree() to sleep to ensure that all relevant
			 * process leaders can be traversed in closef().
			 */
			fdp->fd_holdleaderscount++;
		} else {
			holdleaders = 0;
		}
	}

	/*
	 * We now hold the fp reference that used to be owned by the
	 * descriptor array.  We have to unlock the FILEDESC *AFTER*
	 * knote_fdclose to prevent a race of the fd getting opened, a knote
	 * added, and deleteing a knote for the new fd.
	 */
	if (__predict_false(!TAILQ_EMPTY(&fdp->fd_kqlist)))
		knote_fdclose(td, fd);

	/*
	 * We need to notify mqueue if the object is of type mqueue.
	 */
	if (__predict_false(fp->f_type == DTYPE_MQUEUE))
		mq_fdclose(td, fd, fp);
	FILEDESC_XUNLOCK(fdp);

	error = closef(fp, td);
	if (holdleaders) {
		FILEDESC_XLOCK(fdp);
		fdp->fd_holdleaderscount--;
		if (fdp->fd_holdleaderscount == 0 &&
		    fdp->fd_holdleaderswakeup != 0) {
			fdp->fd_holdleaderswakeup = 0;
			wakeup(&fdp->fd_holdleaderscount);
		}
		FILEDESC_XUNLOCK(fdp);
	}
	return (error);
}