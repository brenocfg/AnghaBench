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
typedef  int uint32_t ;
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct linux_pemuldata {int flags; int /*<<< orphan*/ * epoll; } ;
struct kevent {int dummy; } ;
struct file {int dummy; } ;
struct epoll_event {int events; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int EV_CLEAR ; 
 int EV_EOF ; 
 int EV_ERROR ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LINUX_EPOLLERR ; 
 int LINUX_EPOLLET ; 
 int LINUX_EPOLLONESHOT ; 
 int LINUX_EPOLLRDHUP ; 
 int LINUX_EPOLL_EVRD ; 
 int LINUX_EPOLL_EVSUP ; 
 int LINUX_EPOLL_EVWR ; 
 int /*<<< orphan*/  LINUX_PEM_XLOCK (struct linux_pemuldata*) ; 
 int /*<<< orphan*/  LINUX_PEM_XUNLOCK (struct linux_pemuldata*) ; 
 int LINUX_XUNSUP_EPOLL ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*,int) ; 
 struct linux_pemuldata* pem_find (struct proc*) ; 

__attribute__((used)) static int
epoll_to_kevent(struct thread *td, struct file *epfp,
    int fd, struct epoll_event *l_event, int *kev_flags,
    struct kevent *kevent, int *nkevents)
{
	uint32_t levents = l_event->events;
	struct linux_pemuldata *pem;
	struct proc *p;

	/* flags related to how event is registered */
	if ((levents & LINUX_EPOLLONESHOT) != 0)
		*kev_flags |= EV_ONESHOT;
	if ((levents & LINUX_EPOLLET) != 0)
		*kev_flags |= EV_CLEAR;
	if ((levents & LINUX_EPOLLERR) != 0)
		*kev_flags |= EV_ERROR;
	if ((levents & LINUX_EPOLLRDHUP) != 0)
		*kev_flags |= EV_EOF;

	/* flags related to what event is registered */
	if ((levents & LINUX_EPOLL_EVRD) != 0) {
		EV_SET(kevent++, fd, EVFILT_READ, *kev_flags, 0, 0, 0);
		++(*nkevents);
	}
	if ((levents & LINUX_EPOLL_EVWR) != 0) {
		EV_SET(kevent++, fd, EVFILT_WRITE, *kev_flags, 0, 0, 0);
		++(*nkevents);
	}

	if ((levents & ~(LINUX_EPOLL_EVSUP)) != 0) {
		p = td->td_proc;

		pem = pem_find(p);
		KASSERT(pem != NULL, ("epoll proc emuldata not found.\n"));
		KASSERT(pem->epoll != NULL, ("epoll proc epolldata not found.\n"));

		LINUX_PEM_XLOCK(pem);
		if ((pem->flags & LINUX_XUNSUP_EPOLL) == 0) {
			pem->flags |= LINUX_XUNSUP_EPOLL;
			LINUX_PEM_XUNLOCK(pem);
			linux_msg(td, "epoll_ctl unsupported flags: 0x%x\n",
			    levents);
		} else
			LINUX_PEM_XUNLOCK(pem);
		return (EINVAL);
	}

	return (0);
}