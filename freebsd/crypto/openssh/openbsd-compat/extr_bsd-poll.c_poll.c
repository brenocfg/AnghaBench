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
struct timeval {int tv_sec; int tv_usec; } ;
struct pollfd {int fd; int events; int revents; } ;
typedef  size_t nfds_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  NFDBITS ; 
 int POLLERR ; 
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 size_t howmany (int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int
poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
	nfds_t i;
	int saved_errno, ret, fd, maxfd = 0;
	fd_set *readfds = NULL, *writefds = NULL, *exceptfds = NULL;
	size_t nmemb;
	struct timeval tv, *tvp = NULL;

	for (i = 0; i < nfds; i++) {
		fd = fds[i].fd;
		if (fd >= FD_SETSIZE) {
			errno = EINVAL;
			return -1;
		}
		maxfd = MAX(maxfd, fd);
	}

	nmemb = howmany(maxfd + 1 , NFDBITS);
	if ((readfds = calloc(nmemb, sizeof(fd_mask))) == NULL ||
	    (writefds = calloc(nmemb, sizeof(fd_mask))) == NULL ||
	    (exceptfds = calloc(nmemb, sizeof(fd_mask))) == NULL) {
		saved_errno = ENOMEM;
		ret = -1;
		goto out;
	}

	/* populate event bit vectors for the events we're interested in */
	for (i = 0; i < nfds; i++) {
		fd = fds[i].fd;
		if (fd == -1)
			continue;
		if (fds[i].events & POLLIN) {
			FD_SET(fd, readfds);
			FD_SET(fd, exceptfds);
		}
		if (fds[i].events & POLLOUT) {
			FD_SET(fd, writefds);
			FD_SET(fd, exceptfds);
		}
	}

	/* poll timeout is msec, select is timeval (sec + usec) */
	if (timeout >= 0) {
		tv.tv_sec = timeout / 1000;
		tv.tv_usec = (timeout % 1000) * 1000;
		tvp = &tv;
	}

	ret = select(maxfd + 1, readfds, writefds, exceptfds, tvp);
	saved_errno = errno;

	/* scan through select results and set poll() flags */
	for (i = 0; i < nfds; i++) {
		fd = fds[i].fd;
		fds[i].revents = 0;
		if (fd == -1)
			continue;
		if (FD_ISSET(fd, readfds)) {
			fds[i].revents |= POLLIN;
		}
		if (FD_ISSET(fd, writefds)) {
			fds[i].revents |= POLLOUT;
		}
		if (FD_ISSET(fd, exceptfds)) {
			fds[i].revents |= POLLERR;
		}
	}

out:
	free(readfds);
	free(writefds);
	free(exceptfds);
	if (ret == -1)
		errno = saved_errno;
	return ret;
}