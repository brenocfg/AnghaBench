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

/* Variables and functions */
 int /*<<< orphan*/  F_DUPFD ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int __rpc_minfd ; 
 int _close (int) ; 
 int _fcntl (int,int /*<<< orphan*/ ,int) ; 
 int _fsync (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 

int
__rpc_raise_fd(int fd)
{
	int nfd;

	if (fd >= __rpc_minfd)
		return (fd);

	if ((nfd = _fcntl(fd, F_DUPFD, __rpc_minfd)) == -1)
		return (fd);

	if (_fsync(nfd) == -1) {
		_close(nfd);
		return (fd);
	}

	if (_close(fd) == -1) {
		/* this is okay, we will syslog an error, then use the new fd */
		(void) syslog(LOG_ERR,
			"could not close() fd %d; mem & fd leak", fd);
	}

	return (nfd);
}