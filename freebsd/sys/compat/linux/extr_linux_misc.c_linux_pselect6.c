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
struct timeval {scalar_t__ tv_sec; } ;
struct timespec {int dummy; } ;
struct thread {scalar_t__* td_retval; } ;
struct linux_pselect6_args {int /*<<< orphan*/ * tsp; int /*<<< orphan*/  exceptfds; int /*<<< orphan*/  writefds; int /*<<< orphan*/  readfds; int /*<<< orphan*/  nfds; int /*<<< orphan*/ * sig; } ;
struct l_timespec {int ss_len; scalar_t__ ss; } ;
struct l_pselect6arg {int ss_len; scalar_t__ ss; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  lts ;
typedef  int /*<<< orphan*/  lpse6 ;
typedef  int /*<<< orphan*/  l_ss ;
typedef  struct l_timespec l_sigset_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LINUX_NFDBITS ; 
 int /*<<< orphan*/ * PTRIN (scalar_t__) ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  TIMEVAL_TO_TIMESPEC (struct timeval*,struct timespec*) ; 
 int copyin (int /*<<< orphan*/ *,struct l_timespec*,int) ; 
 int copyout (struct l_timespec*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ itimerfix (struct timeval*) ; 
 int kern_pselect (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_to_bsd_sigset (struct l_timespec*,int /*<<< orphan*/ *) ; 
 int linux_to_native_timespec (struct timespec*,struct l_timespec*) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int native_to_linux_timespec (struct l_timespec*,struct timespec*) ; 
 int /*<<< orphan*/  timevalclear (struct timeval*) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,struct timeval*) ; 

int
linux_pselect6(struct thread *td, struct linux_pselect6_args *args)
{
	struct timeval utv, tv0, tv1, *tvp;
	struct l_pselect6arg lpse6;
	struct l_timespec lts;
	struct timespec uts;
	l_sigset_t l_ss;
	sigset_t *ssp;
	sigset_t ss;
	int error;

	ssp = NULL;
	if (args->sig != NULL) {
		error = copyin(args->sig, &lpse6, sizeof(lpse6));
		if (error != 0)
			return (error);
		if (lpse6.ss_len != sizeof(l_ss))
			return (EINVAL);
		if (lpse6.ss != 0) {
			error = copyin(PTRIN(lpse6.ss), &l_ss,
			    sizeof(l_ss));
			if (error != 0)
				return (error);
			linux_to_bsd_sigset(&l_ss, &ss);
			ssp = &ss;
		}
	}

	/*
	 * Currently glibc changes nanosecond number to microsecond.
	 * This mean losing precision but for now it is hardly seen.
	 */
	if (args->tsp != NULL) {
		error = copyin(args->tsp, &lts, sizeof(lts));
		if (error != 0)
			return (error);
		error = linux_to_native_timespec(&uts, &lts);
		if (error != 0)
			return (error);

		TIMESPEC_TO_TIMEVAL(&utv, &uts);
		if (itimerfix(&utv))
			return (EINVAL);

		microtime(&tv0);
		tvp = &utv;
	} else
		tvp = NULL;

	error = kern_pselect(td, args->nfds, args->readfds, args->writefds,
	    args->exceptfds, tvp, ssp, LINUX_NFDBITS);

	if (error == 0 && args->tsp != NULL) {
		if (td->td_retval[0] != 0) {
			/*
			 * Compute how much time was left of the timeout,
			 * by subtracting the current time and the time
			 * before we started the call, and subtracting
			 * that result from the user-supplied value.
			 */

			microtime(&tv1);
			timevalsub(&tv1, &tv0);
			timevalsub(&utv, &tv1);
			if (utv.tv_sec < 0)
				timevalclear(&utv);
		} else
			timevalclear(&utv);

		TIMEVAL_TO_TIMESPEC(&utv, &uts);

		error = native_to_linux_timespec(&lts, &uts);
		if (error == 0)
			error = copyout(&lts, args->tsp, sizeof(lts));
	}

	return (error);
}