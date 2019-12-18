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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __svc_clean_idle (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int _select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  _warn (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_fd_lock ; 
 int /*<<< orphan*/  svc_fdset ; 
 int /*<<< orphan*/  svc_getreqset (int /*<<< orphan*/ *) ; 
 scalar_t__ svc_maxfd ; 

void
svc_run(void)
{
	fd_set readfds, cleanfds;
	struct timeval timeout;

	timeout.tv_sec = 30;
	timeout.tv_usec = 0;

	for (;;) {
		rwlock_rdlock(&svc_fd_lock);
		readfds = svc_fdset;
		cleanfds = svc_fdset;
		rwlock_unlock(&svc_fd_lock);
		switch (_select(svc_maxfd+1, &readfds, NULL, NULL, &timeout)) {
		case -1:
			FD_ZERO(&readfds);
			if (errno == EINTR) {
				continue;
			}
			_warn("svc_run: - select failed");
			return;
		case 0:
			__svc_clean_idle(&cleanfds, 30, FALSE);
			continue;
		default:
			svc_getreqset(&readfds);
		}
	}
}