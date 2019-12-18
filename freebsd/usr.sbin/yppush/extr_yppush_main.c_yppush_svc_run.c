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
 int /*<<< orphan*/  errno ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_fdset ; 
 int /*<<< orphan*/  svc_getreqset (int /*<<< orphan*/ *) ; 
 scalar_t__ svc_maxfd ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 

__attribute__((used)) static int
yppush_svc_run(int timeout_secs)
{
	int rc;
	fd_set readfds;
	struct timeval timeout;

	timeout.tv_usec = 0;
	timeout.tv_sec = timeout_secs;

retry:
	readfds = svc_fdset;
	rc = select(svc_maxfd + 1, &readfds, NULL, NULL, &timeout);
	switch (rc) {
	case -1:
		if (errno == EINTR)
			goto retry;
		yp_error("select failed: %s", strerror(errno));
		break;
	case 0:
		yp_error("select() timed out");
		break;
	default:
		svc_getreqset(&readfds);
		break;
	}
	return rc;
}