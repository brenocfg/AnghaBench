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
struct thread {int dummy; } ;
struct poll_args {int timeout; int /*<<< orphan*/  nfds; int /*<<< orphan*/  fds; } ;

/* Variables and functions */
 int EINVAL ; 
 int INFTIM ; 
 int kern_poll (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *) ; 

int
sys_poll(struct thread *td, struct poll_args *uap)
{
	struct timespec ts, *tsp;

	if (uap->timeout != INFTIM) {
		if (uap->timeout < 0)
			return (EINVAL);
		ts.tv_sec = uap->timeout / 1000;
		ts.tv_nsec = (uap->timeout % 1000) * 1000000;
		tsp = &ts;
	} else
		tsp = NULL;

	return (kern_poll(td, uap->fds, uap->nfds, tsp, NULL));
}