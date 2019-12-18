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
typedef  int /*<<< orphan*/  ts ;
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct ppoll_args {int /*<<< orphan*/  nfds; int /*<<< orphan*/  fds; int /*<<< orphan*/ * set; int /*<<< orphan*/ * ts; } ;
typedef  struct timespec sigset_t ;
typedef  int /*<<< orphan*/  set ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ *,struct timespec*,int) ; 
 int kern_poll (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,struct timespec*) ; 

int
sys_ppoll(struct thread *td, struct ppoll_args *uap)
{
	struct timespec ts, *tsp;
	sigset_t set, *ssp;
	int error;

	if (uap->ts != NULL) {
		error = copyin(uap->ts, &ts, sizeof(ts));
		if (error)
			return (error);
		tsp = &ts;
	} else
		tsp = NULL;
	if (uap->set != NULL) {
		error = copyin(uap->set, &set, sizeof(set));
		if (error)
			return (error);
		ssp = &set;
	} else
		ssp = NULL;
	/*
	 * fds is still a pointer to user space. kern_poll() will
	 * take care of copyin that array to the kernel space.
	 */

	return (kern_poll(td, uap->fds, uap->nfds, tsp, ssp));
}