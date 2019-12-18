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
struct kevent {int flags; int filter; } ;
struct epoll_event {int /*<<< orphan*/  events; } ;

/* Variables and functions */
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int EV_EOF ; 
 int EV_ERROR ; 
 int /*<<< orphan*/  LINUX_EPOLLERR ; 
 int /*<<< orphan*/  LINUX_EPOLLIN ; 
 int /*<<< orphan*/  LINUX_EPOLLOUT ; 
 int /*<<< orphan*/  LINUX_EPOLLRDHUP ; 

__attribute__((used)) static void
kevent_to_epoll(struct kevent *kevent, struct epoll_event *l_event)
{

	if ((kevent->flags & EV_ERROR) != 0) {
		l_event->events = LINUX_EPOLLERR;
		return;
	}

	/* XXX EPOLLPRI, EPOLLHUP */
	switch (kevent->filter) {
	case EVFILT_READ:
		l_event->events = LINUX_EPOLLIN;
		if ((kevent->flags & EV_EOF) != 0)
			l_event->events |= LINUX_EPOLLRDHUP;
	break;
	case EVFILT_WRITE:
		l_event->events = LINUX_EPOLLOUT;
	break;
	}
}