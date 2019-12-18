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
typedef  int /*<<< orphan*/  ts32 ;
struct timespec32 {int dummy; } ;
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct freebsd32_ppoll_args {int /*<<< orphan*/  nfds; int /*<<< orphan*/  fds; int /*<<< orphan*/ * set; int /*<<< orphan*/ * ts; } ;
typedef  struct timespec32 sigset_t ;
typedef  int /*<<< orphan*/  set ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct timespec32,struct timespec,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ *,struct timespec32*,int) ; 
 int kern_poll (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,struct timespec32*) ; 
 int /*<<< orphan*/  tv_nsec ; 
 int /*<<< orphan*/  tv_sec ; 

int
freebsd32_ppoll(struct thread *td, struct freebsd32_ppoll_args *uap)
{
	struct timespec32 ts32;
	struct timespec ts, *tsp;
	sigset_t set, *ssp;
	int error;

	if (uap->ts != NULL) {
		error = copyin(uap->ts, &ts32, sizeof(ts32));
		if (error != 0)
			return (error);
		CP(ts32, ts, tv_sec);
		CP(ts32, ts, tv_nsec);
		tsp = &ts;
	} else
		tsp = NULL;
	if (uap->set != NULL) {
		error = copyin(uap->set, &set, sizeof(set));
		if (error != 0)
			return (error);
		ssp = &set;
	} else
		ssp = NULL;

	return (kern_poll(td, uap->fds, uap->nfds, tsp, ssp));
}