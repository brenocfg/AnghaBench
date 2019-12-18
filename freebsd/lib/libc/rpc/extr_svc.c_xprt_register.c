#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int xp_fd; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 TYPE_1__** __svc_xports ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mem_alloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,char,int) ; 
 int /*<<< orphan*/  rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_fd_lock ; 
 int /*<<< orphan*/  svc_fdset ; 
 int /*<<< orphan*/  svc_maxfd ; 

void
xprt_register(SVCXPRT *xprt)
{
	int sock;

	assert(xprt != NULL);

	sock = xprt->xp_fd;

	rwlock_wrlock(&svc_fd_lock);
	if (__svc_xports == NULL) {
		__svc_xports = (SVCXPRT **)
			mem_alloc((FD_SETSIZE + 1) * sizeof(SVCXPRT *));
		if (__svc_xports == NULL) {
			rwlock_unlock(&svc_fd_lock);
			return;
		}
		memset(__svc_xports, '\0', (FD_SETSIZE + 1) * sizeof(SVCXPRT *));
	}
	if (sock < FD_SETSIZE) {
		__svc_xports[sock] = xprt;
		FD_SET(sock, &svc_fdset);
		svc_maxfd = max(svc_maxfd, sock);
	} else if (sock == FD_SETSIZE)
		__svc_xports[sock] = xprt;
	rwlock_unlock(&svc_fd_lock);
}