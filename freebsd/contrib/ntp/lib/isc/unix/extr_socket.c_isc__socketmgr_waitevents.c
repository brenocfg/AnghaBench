#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct dvpoll {int dp_timeout; int /*<<< orphan*/  dp_nfds; int /*<<< orphan*/  dp_fds; } ;
struct TYPE_6__ {int nevents; int /*<<< orphan*/  writeset; int /*<<< orphan*/  readset; scalar_t__ maxfd; } ;
typedef  TYPE_1__ isc_socketwait_t ;
typedef  int /*<<< orphan*/  isc_socketmgr_t ;
struct TYPE_7__ {scalar_t__ maxfd; int /*<<< orphan*/  write_fds_copy; int /*<<< orphan*/  read_fds_copy; int /*<<< orphan*/  fd_bufsize; int /*<<< orphan*/  write_fds; int /*<<< orphan*/  read_fds; int /*<<< orphan*/  devpoll_fd; int /*<<< orphan*/  nevents; int /*<<< orphan*/  events; int /*<<< orphan*/  epoll_fd; int /*<<< orphan*/  kqueue_fd; } ;
typedef  TYPE_2__ isc__socketmgr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_POLL ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int epoll_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvpoll*) ; 
 int kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval*) ; 
 TYPE_2__* socketmgr ; 
 TYPE_1__ swait_private ; 

int
isc__socketmgr_waitevents(isc_socketmgr_t *manager0, struct timeval *tvp,
			  isc_socketwait_t **swaitp)
{
	isc__socketmgr_t *manager = (isc__socketmgr_t *)manager0;


	int n;
#ifdef USE_KQUEUE
	struct timespec ts, *tsp;
#endif
#ifdef USE_EPOLL
	int timeout;
#endif
#ifdef USE_DEVPOLL
	struct dvpoll dvp;
#endif

	REQUIRE(swaitp != NULL && *swaitp == NULL);

#ifdef USE_SHARED_MANAGER
	if (manager == NULL)
		manager = socketmgr;
#endif
	if (manager == NULL)
		return (0);

#ifdef USE_KQUEUE
	if (tvp != NULL) {
		ts.tv_sec = tvp->tv_sec;
		ts.tv_nsec = tvp->tv_usec * 1000;
		tsp = &ts;
	} else
		tsp = NULL;
	swait_private.nevents = kevent(manager->kqueue_fd, NULL, 0,
				       manager->events, manager->nevents,
				       tsp);
	n = swait_private.nevents;
#elif defined(USE_EPOLL)
	if (tvp != NULL)
		timeout = tvp->tv_sec * 1000 + (tvp->tv_usec + 999) / 1000;
	else
		timeout = -1;
	swait_private.nevents = epoll_wait(manager->epoll_fd,
					   manager->events,
					   manager->nevents, timeout);
	n = swait_private.nevents;
#elif defined(USE_DEVPOLL)
	dvp.dp_fds = manager->events;
	dvp.dp_nfds = manager->nevents;
	if (tvp != NULL) {
		dvp.dp_timeout = tvp->tv_sec * 1000 +
			(tvp->tv_usec + 999) / 1000;
	} else
		dvp.dp_timeout = -1;
	swait_private.nevents = ioctl(manager->devpoll_fd, DP_POLL, &dvp);
	n = swait_private.nevents;
#elif defined(USE_SELECT)
	memcpy(manager->read_fds_copy, manager->read_fds,  manager->fd_bufsize);
	memcpy(manager->write_fds_copy, manager->write_fds,
	       manager->fd_bufsize);

	swait_private.readset = manager->read_fds_copy;
	swait_private.writeset = manager->write_fds_copy;
	swait_private.maxfd = manager->maxfd + 1;

	n = select(swait_private.maxfd, swait_private.readset,
		   swait_private.writeset, NULL, tvp);
#endif

	*swaitp = &swait_private;
	return (n);
}