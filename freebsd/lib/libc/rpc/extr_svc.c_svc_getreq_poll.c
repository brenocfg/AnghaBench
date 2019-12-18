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
struct pollfd {int revents; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int POLLNVAL ; 
 int /*<<< orphan*/  rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_fd_lock ; 
 int /*<<< orphan*/  svc_fdset ; 
 int /*<<< orphan*/  svc_getreq_common (int /*<<< orphan*/ ) ; 

void
svc_getreq_poll(struct pollfd *pfdp, int pollretval)
{
	int i;
	int fds_found;

	for (i = fds_found = 0; fds_found < pollretval; i++) {
		struct pollfd *p = &pfdp[i];

		if (p->revents) {
			/* fd has input waiting */
			fds_found++;
			/*
			 *	We assume that this function is only called
			 *	via someone _select()ing from svc_fdset or
			 *	_poll()ing from svc_pollset[].  Thus it's safe
			 *	to handle the POLLNVAL event by simply turning
			 *	the corresponding bit off in svc_fdset.  The
			 *	svc_pollset[] array is derived from svc_fdset
			 *	and so will also be updated eventually.
			 *
			 *	XXX Should we do an xprt_unregister() instead?
			 */
			if (p->revents & POLLNVAL) {
				rwlock_wrlock(&svc_fd_lock);
				FD_CLR(p->fd, &svc_fdset);
				rwlock_unlock(&svc_fd_lock);
			} else
				svc_getreq_common(p->fd);
		}
	}
}