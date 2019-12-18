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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int accept (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  uc_dbgmsg (char*) ; 
 int /*<<< orphan*/  uc_logmsg (char*) ; 
 int /*<<< orphan*/  uc_logmsgx (char*) ; 

int
uc_socket_accept(int listenfd)
{
	fd_set rset;
	struct timeval tv;
	int fd, rv, val;

	uc_dbgmsg("accept");

	FD_ZERO(&rset);
	FD_SET(listenfd, &rset);
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;
	rv = select(listenfd + 1, &rset, (fd_set *)NULL, (fd_set *)NULL, &tv);
	if (rv < 0) {
		uc_logmsg("socket_accept: select");
		return (-1);
	}
	if (rv == 0) {
		uc_logmsgx("socket_accept: select timeout");
		return (-1);
	}

	fd = accept(listenfd, (struct sockaddr *)NULL, (socklen_t *)NULL);
	if (fd < 0) {
		uc_logmsg("socket_accept: accept");
		return (-1);
	}

	val = fcntl(fd, F_GETFL, 0);
	if (val < 0) {
		uc_logmsg("socket_accept: fcntl(F_GETFL)");
		goto failed;
	}
	if (fcntl(fd, F_SETFL, val & ~O_NONBLOCK) < 0) {
		uc_logmsg("socket_accept: fcntl(F_SETFL)");
		goto failed;
	}

	return (fd);

failed:
	if (close(fd) < 0)
		uc_logmsg("socket_accept: close");
	return (-1);
}