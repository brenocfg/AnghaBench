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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int _rpc_dtablesize () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getpid () ; 
 int select (int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int svc_fds ; 
 int svc_fdset ; 
 int /*<<< orphan*/  svc_getreqset (int*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
ypxfrd_svc_run(void)
{
#ifdef FD_SETSIZE
	fd_set readfds;
#else
	int readfds;
#endif /* def FD_SETSIZE */
	extern int forked;
	int pid;
	int fd_setsize = _rpc_dtablesize();

	/* Establish the identity of the parent ypserv process. */
	pid = getpid();

	for (;;) {
#ifdef FD_SETSIZE
		readfds = svc_fdset;
#else
		readfds = svc_fds;
#endif /* def FD_SETSIZE */
		switch (select(fd_setsize, &readfds, NULL, NULL,
			       (struct timeval *)0)) {
		case -1:
			if (errno == EINTR) {
				continue;
			}
			warn("svc_run: - select failed");
			return;
		case 0:
			continue;
		default:
			svc_getreqset(&readfds);
			if (forked && pid != getpid())
				exit(0);
		}
	}
}