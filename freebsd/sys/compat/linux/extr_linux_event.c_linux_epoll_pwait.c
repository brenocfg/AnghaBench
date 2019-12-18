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
struct thread {int dummy; } ;
struct linux_epoll_pwait_args {int sigsetsize; int /*<<< orphan*/  timeout; int /*<<< orphan*/  maxevents; int /*<<< orphan*/  events; int /*<<< orphan*/  epfd; int /*<<< orphan*/ * mask; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  l_sigset_t ;

/* Variables and functions */
 int EINVAL ; 
 int copyin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int linux_epoll_wait_common (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_to_bsd_sigset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
linux_epoll_pwait(struct thread *td, struct linux_epoll_pwait_args *args)
{
	sigset_t mask, *pmask;
	l_sigset_t lmask;
	int error;

	if (args->mask != NULL) {
		if (args->sigsetsize != sizeof(l_sigset_t))
			return (EINVAL);
		error = copyin(args->mask, &lmask, sizeof(l_sigset_t));
		if (error != 0)
			return (error);
		linux_to_bsd_sigset(&lmask, &mask);
		pmask = &mask;
	} else
		pmask = NULL;
	return (linux_epoll_wait_common(td, args->epfd, args->events,
	    args->maxevents, args->timeout, pmask));
}