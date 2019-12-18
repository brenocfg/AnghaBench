#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int ident; int fd; scalar_t__ revents; int /*<<< orphan*/  events; int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; } ;
struct kevent {int ident; int fd; scalar_t__ revents; int /*<<< orphan*/  events; int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; } ;
struct epoll_event {struct pollfd data; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  pfd ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  write_fds; int /*<<< orphan*/  read_fds; int /*<<< orphan*/ * fdlock; TYPE_1__* fdpollinfo; int /*<<< orphan*/  devpoll_fd; int /*<<< orphan*/  epoll_fd; int /*<<< orphan*/  kqueue_fd; } ;
typedef  TYPE_2__ isc__socketmgr_t ;
typedef  int /*<<< orphan*/  evchange ;
struct TYPE_4__ {int want_read; int want_write; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLLOUT ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/  EV_ADD ; 
 int FDLOCK_ID (int) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int SELECT_POKE_READ ; 
 int SELECT_POKE_WRITE ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  isc__errno2result (scalar_t__) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct pollfd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct pollfd*,int /*<<< orphan*/ ,int) ; 
 int write (int /*<<< orphan*/ ,struct pollfd*,int) ; 

__attribute__((used)) static inline isc_result_t
watch_fd(isc__socketmgr_t *manager, int fd, int msg) {
	isc_result_t result = ISC_R_SUCCESS;

#ifdef USE_KQUEUE
	struct kevent evchange;

	memset(&evchange, 0, sizeof(evchange));
	if (msg == SELECT_POKE_READ)
		evchange.filter = EVFILT_READ;
	else
		evchange.filter = EVFILT_WRITE;
	evchange.flags = EV_ADD;
	evchange.ident = fd;
	if (kevent(manager->kqueue_fd, &evchange, 1, NULL, 0, NULL) != 0)
		result = isc__errno2result(errno);

	return (result);
#elif defined(USE_EPOLL)
	struct epoll_event event;

	if (msg == SELECT_POKE_READ)
		event.events = EPOLLIN;
	else
		event.events = EPOLLOUT;
	memset(&event.data, 0, sizeof(event.data));
	event.data.fd = fd;
	if (epoll_ctl(manager->epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1 &&
	    errno != EEXIST) {
		result = isc__errno2result(errno);
	}

	return (result);
#elif defined(USE_DEVPOLL)
	struct pollfd pfd;
	int lockid = FDLOCK_ID(fd);

	memset(&pfd, 0, sizeof(pfd));
	if (msg == SELECT_POKE_READ)
		pfd.events = POLLIN;
	else
		pfd.events = POLLOUT;
	pfd.fd = fd;
	pfd.revents = 0;
	LOCK(&manager->fdlock[lockid]);
	if (write(manager->devpoll_fd, &pfd, sizeof(pfd)) == -1)
		result = isc__errno2result(errno);
	else {
		if (msg == SELECT_POKE_READ)
			manager->fdpollinfo[fd].want_read = 1;
		else
			manager->fdpollinfo[fd].want_write = 1;
	}
	UNLOCK(&manager->fdlock[lockid]);

	return (result);
#elif defined(USE_SELECT)
	LOCK(&manager->lock);
	if (msg == SELECT_POKE_READ)
		FD_SET(fd, manager->read_fds);
	if (msg == SELECT_POKE_WRITE)
		FD_SET(fd, manager->write_fds);
	UNLOCK(&manager->lock);

	return (result);
#endif
}