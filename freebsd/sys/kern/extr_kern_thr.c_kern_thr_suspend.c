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
struct timeval {int dummy; } ;
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct thread {int td_pflags; int td_flags; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_mtx; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  PCATCH ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int TDF_THRWAKEUP ; 
 int TDP_WAKEUP ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int msleep (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int tvtohz (struct timeval*) ; 

int
kern_thr_suspend(struct thread *td, struct timespec *tsp)
{
	struct proc *p = td->td_proc;
	struct timeval tv;
	int error = 0;
	int timo = 0;

	if (td->td_pflags & TDP_WAKEUP) {
		td->td_pflags &= ~TDP_WAKEUP;
		return (0);
	}

	if (tsp != NULL) {
		if (tsp->tv_sec == 0 && tsp->tv_nsec == 0)
			error = EWOULDBLOCK;
		else {
			TIMESPEC_TO_TIMEVAL(&tv, tsp);
			timo = tvtohz(&tv);
		}
	}

	PROC_LOCK(p);
	if (error == 0 && (td->td_flags & TDF_THRWAKEUP) == 0)
		error = msleep((void *)td, &p->p_mtx,
			 PCATCH, "lthr", timo);

	if (td->td_flags & TDF_THRWAKEUP) {
		thread_lock(td);
		td->td_flags &= ~TDF_THRWAKEUP;
		thread_unlock(td);
		PROC_UNLOCK(p);
		return (0);
	}
	PROC_UNLOCK(p);
	if (error == EWOULDBLOCK)
		error = ETIMEDOUT;
	else if (error == ERESTART) {
		if (timo != 0)
			error = EINTR;
	}
	return (error);
}