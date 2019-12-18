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
struct timespec {scalar_t__ tv_sec; } ;
struct thread {scalar_t__* td_retval; } ;
struct linux_ppoll_args {int ssize; int /*<<< orphan*/ * tsp; int /*<<< orphan*/  nfds; int /*<<< orphan*/  fds; int /*<<< orphan*/ * sset; } ;
struct l_timespec {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  lts ;
typedef  int /*<<< orphan*/  l_ss ;
typedef  struct l_timespec l_sigset_t ;

/* Variables and functions */
 int EINVAL ; 
 int copyin (int /*<<< orphan*/ *,struct l_timespec*,int) ; 
 int copyout (struct l_timespec*,int /*<<< orphan*/ *,int) ; 
 int kern_poll (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_to_bsd_sigset (struct l_timespec*,int /*<<< orphan*/ *) ; 
 int linux_to_native_timespec (struct timespec*,struct l_timespec*) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 int native_to_linux_timespec (struct l_timespec*,struct timespec*) ; 
 int /*<<< orphan*/  timespecclear (struct timespec*) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 

int
linux_ppoll(struct thread *td, struct linux_ppoll_args *args)
{
	struct timespec ts0, ts1;
	struct l_timespec lts;
	struct timespec uts, *tsp;
	l_sigset_t l_ss;
	sigset_t *ssp;
	sigset_t ss;
	int error;

	if (args->sset != NULL) {
		if (args->ssize != sizeof(l_ss))
			return (EINVAL);
		error = copyin(args->sset, &l_ss, sizeof(l_ss));
		if (error)
			return (error);
		linux_to_bsd_sigset(&l_ss, &ss);
		ssp = &ss;
	} else
		ssp = NULL;
	if (args->tsp != NULL) {
		error = copyin(args->tsp, &lts, sizeof(lts));
		if (error)
			return (error);
		error = linux_to_native_timespec(&uts, &lts);
		if (error != 0)
			return (error);

		nanotime(&ts0);
		tsp = &uts;
	} else
		tsp = NULL;

	error = kern_poll(td, args->fds, args->nfds, tsp, ssp);

	if (error == 0 && args->tsp != NULL) {
		if (td->td_retval[0]) {
			nanotime(&ts1);
			timespecsub(&ts1, &ts0, &ts1);
			timespecsub(&uts, &ts1, &uts);
			if (uts.tv_sec < 0)
				timespecclear(&uts);
		} else
			timespecclear(&uts);

		error = native_to_linux_timespec(&lts, &uts);
		if (error == 0)
			error = copyout(&lts, args->tsp, sizeof(lts));
	}

	return (error);
}