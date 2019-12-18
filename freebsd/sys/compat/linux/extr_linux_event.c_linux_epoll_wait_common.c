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
struct timespec {int tv_sec; int tv_nsec; } ;
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_flags; int /*<<< orphan*/  td_pflags; } ;
struct kevent_copyops {int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; struct epoll_copyout_args* member_0; } ;
struct file {scalar_t__ f_type; } ;
struct epoll_event {int dummy; } ;
struct epoll_copyout_args {int error; scalar_t__ count; int /*<<< orphan*/  p; struct epoll_event* leventlist; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_KQUEUE_EVENT ; 
 scalar_t__ DTYPE_KQUEUE ; 
 int EINVAL ; 
 int LINUX_MAX_EVENTS ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TDF_ASTPENDING ; 
 int /*<<< orphan*/  TDP_OLDMASK ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_kev_copyout ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ ,struct file**) ; 
 int kern_kevent_fp (struct thread*,struct file*,int /*<<< orphan*/ ,int,struct kevent_copyops*,struct timespec*) ; 
 int kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static int
linux_epoll_wait_common(struct thread *td, int epfd, struct epoll_event *events,
    int maxevents, int timeout, sigset_t *uset)
{
	struct epoll_copyout_args coargs;
	struct kevent_copyops k_ops = { &coargs,
					epoll_kev_copyout,
					NULL};
	struct timespec ts, *tsp;
	cap_rights_t rights;
	struct file *epfp;
	sigset_t omask;
	int error;

	if (maxevents <= 0 || maxevents > LINUX_MAX_EVENTS)
		return (EINVAL);

	error = fget(td, epfd,
	    cap_rights_init(&rights, CAP_KQUEUE_EVENT), &epfp);
	if (error != 0)
		return (error);
	if (epfp->f_type != DTYPE_KQUEUE) {
		error = EINVAL;
		goto leave1;
	}
	if (uset != NULL) {
		error = kern_sigprocmask(td, SIG_SETMASK, uset,
		    &omask, 0);
		if (error != 0)
			goto leave1;
		td->td_pflags |= TDP_OLDMASK;
		/*
		 * Make sure that ast() is called on return to
		 * usermode and TDP_OLDMASK is cleared, restoring old
		 * sigmask.
		 */
		thread_lock(td);
		td->td_flags |= TDF_ASTPENDING;
		thread_unlock(td);
	}


	coargs.leventlist = events;
	coargs.p = td->td_proc;
	coargs.count = 0;
	coargs.error = 0;

	if (timeout != -1) {
		if (timeout < 0) {
			error = EINVAL;
			goto leave0;
		}
		/* Convert from milliseconds to timespec. */
		ts.tv_sec = timeout / 1000;
		ts.tv_nsec = (timeout % 1000) * 1000000;
		tsp = &ts;
	} else {
		tsp = NULL;
	}

	error = kern_kevent_fp(td, epfp, 0, maxevents, &k_ops, tsp);
	if (error == 0 && coargs.error != 0)
		error = coargs.error;

	/*
	 * kern_kevent might return ENOMEM which is not expected from epoll_wait.
	 * Maybe we should translate that but I don't think it matters at all.
	 */
	if (error == 0)
		td->td_retval[0] = coargs.count;

leave0:
	if (uset != NULL)
		error = kern_sigprocmask(td, SIG_SETMASK, &omask,
		    NULL, 0);
leave1:
	fdrop(epfp, td);
	return (error);
}