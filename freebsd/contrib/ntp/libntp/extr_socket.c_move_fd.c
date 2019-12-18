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
typedef  int SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE (int) ; 
 scalar_t__ FD_CHUNK ; 
 scalar_t__ FD_PREFERRED_SOCKBOUNDARY ; 
 scalar_t__ FOPEN_MAX ; 
 int /*<<< orphan*/  F_DUPFD ; 
 scalar_t__ GETDTABLESIZE () ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  TRACE (int,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int max (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

SOCKET
move_fd(
	SOCKET fd
	)
{
#if !defined(SYS_WINNT) && defined(F_DUPFD)
#ifndef FD_CHUNK
#define FD_CHUNK	10
#endif
#ifndef FOPEN_MAX
#define FOPEN_MAX	20
#endif
/*
 * number of fds we would like to have for
 * stdio FILE* available.
 * we can pick a "low" number as our use of
 * FILE* is limited to log files and temporarily
 * to data and config files. Except for log files
 * we don't keep the other FILE* open beyond the
 * scope of the function that opened it.
 */
#ifndef FD_PREFERRED_SOCKBOUNDARY
#define FD_PREFERRED_SOCKBOUNDARY 48
#endif

	static SOCKET socket_boundary = -1;
	SOCKET newfd;

	REQUIRE((int)fd >= 0);

	/*
	 * check whether boundary has be set up
	 * already
	 */
	if (socket_boundary == -1) {
		socket_boundary = max(0, min(GETDTABLESIZE() - FD_CHUNK,
					     min(FOPEN_MAX, FD_PREFERRED_SOCKBOUNDARY)));
		TRACE(1, ("move_fd: estimated max descriptors: %d, "
			  "initial socket boundary: %d\n",
			  GETDTABLESIZE(), socket_boundary));
	}

	/*
	 * Leave a space for stdio to work in. potentially moving the
	 * socket_boundary lower until allocation succeeds.
	 */
	do {
		if (fd >= 0 && fd < socket_boundary) {
			/* inside reserved range: attempt to move fd */
			newfd = fcntl(fd, F_DUPFD, socket_boundary);

			if (newfd != -1) {
				/* success: drop the old one - return the new one */
				close(fd);
				return newfd;
			}
		} else {
			/* outside reserved range: no work - return the original one */
			return fd;
		}
		socket_boundary = max(0, socket_boundary - FD_CHUNK);
		TRACE(1, ("move_fd: selecting new socket boundary: %d\n",
			  socket_boundary));
	} while (socket_boundary > 0);
#else
	ENSURE((int)fd >= 0);
#endif /* !defined(SYS_WINNT) && defined(F_DUPFD) */
	return fd;
}