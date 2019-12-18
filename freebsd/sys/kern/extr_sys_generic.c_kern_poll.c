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
typedef  int u_int ;
typedef  int time_t ;
struct timespec {scalar_t__ tv_sec; int tv_nsec; } ;
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_flags; int /*<<< orphan*/  td_pflags; int /*<<< orphan*/  td_oldsigmask; } ;
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int sbintime_t ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 int FD_SETSIZE ; 
 int INT32_MAX ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TDF_ASTPENDING ; 
 int /*<<< orphan*/  TDP_OLDMASK ; 
 scalar_t__ TIMESEL (int*,int) ; 
 int copyin (struct pollfd*,struct pollfd*,int) ; 
 int /*<<< orphan*/  free (struct pollfd*,int /*<<< orphan*/ ) ; 
 int kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pollfd* mallocarray (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int maxfilesperproc ; 
 int nitems (struct pollfd*) ; 
 int pollout (struct thread*,struct pollfd*,struct pollfd*,int) ; 
 int pollrescan (struct thread*) ; 
 int pollscan (struct thread*,struct pollfd*,int) ; 
 int /*<<< orphan*/  seltdclear (struct thread*) ; 
 int /*<<< orphan*/  seltdinit (struct thread*) ; 
 int seltdwait (struct thread*,int,int) ; 
 int tc_precexp ; 
 scalar_t__ tc_tick_sbt ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int tstosbt (struct timespec) ; 

int
kern_poll(struct thread *td, struct pollfd *ufds, u_int nfds,
    struct timespec *tsp, sigset_t *uset)
{
	struct pollfd *kfds;
	struct pollfd stackfds[32];
	sbintime_t sbt, precision, tmp;
	time_t over;
	struct timespec ts;
	int error;

	precision = 0;
	if (tsp != NULL) {
		if (tsp->tv_sec < 0)
			return (EINVAL);
		if (tsp->tv_nsec < 0 || tsp->tv_nsec >= 1000000000)
			return (EINVAL);
		if (tsp->tv_sec == 0 && tsp->tv_nsec == 0)
			sbt = 0;
		else {
			ts = *tsp;
			if (ts.tv_sec > INT32_MAX / 2) {
				over = ts.tv_sec - INT32_MAX / 2;
				ts.tv_sec -= over;
			} else
				over = 0;
			tmp = tstosbt(ts);
			precision = tmp;
			precision >>= tc_precexp;
			if (TIMESEL(&sbt, tmp))
				sbt += tc_tick_sbt;
			sbt += tmp;
		}
	} else
		sbt = -1;

	/*
	 * This is kinda bogus.  We have fd limits, but that is not
	 * really related to the size of the pollfd array.  Make sure
	 * we let the process use at least FD_SETSIZE entries and at
	 * least enough for the system-wide limits.  We want to be reasonably
	 * safe, but not overly restrictive.
	 */
	if (nfds > maxfilesperproc && nfds > FD_SETSIZE) 
		return (EINVAL);
	if (nfds > nitems(stackfds))
		kfds = mallocarray(nfds, sizeof(*kfds), M_TEMP, M_WAITOK);
	else
		kfds = stackfds;
	error = copyin(ufds, kfds, nfds * sizeof(*kfds));
	if (error)
		goto done;

	if (uset != NULL) {
		error = kern_sigprocmask(td, SIG_SETMASK, uset,
		    &td->td_oldsigmask, 0);
		if (error)
			goto done;
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

	seltdinit(td);
	/* Iterate until the timeout expires or descriptors become ready. */
	for (;;) {
		error = pollscan(td, kfds, nfds);
		if (error || td->td_retval[0] != 0)
			break;
		error = seltdwait(td, sbt, precision);
		if (error)
			break;
		error = pollrescan(td);
		if (error || td->td_retval[0] != 0)
			break;
	}
	seltdclear(td);

done:
	/* poll is not restarted after signals... */
	if (error == ERESTART)
		error = EINTR;
	if (error == EWOULDBLOCK)
		error = 0;
	if (error == 0) {
		error = pollout(td, kfds, ufds, nfds);
		if (error)
			goto out;
	}
out:
	if (nfds > nitems(stackfds))
		free(kfds, M_TEMP);
	return (error);
}