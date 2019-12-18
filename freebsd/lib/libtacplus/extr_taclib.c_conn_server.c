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
struct tac_server {int /*<<< orphan*/  timeout; int /*<<< orphan*/  addr; } ;
struct tac_handle {size_t cur_server; int fd; struct tac_server* servers; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  generr (struct tac_handle*,char*,...) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int
conn_server(struct tac_handle *h)
{
	const struct tac_server *srvp = &h->servers[h->cur_server];
	int flags;

	if ((h->fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		generr(h, "Cannot create socket: %s", strerror(errno));
		return -1;
	}
	if ((flags = fcntl(h->fd, F_GETFL, 0)) == -1 ||
	    fcntl(h->fd, F_SETFL, flags | O_NONBLOCK) == -1) {
		generr(h, "Cannot set non-blocking mode on socket: %s",
		    strerror(errno));
		close(h->fd);
		h->fd = -1;
		return -1;
	}
	if (connect(h->fd, (struct sockaddr *)&srvp->addr,
	    sizeof srvp->addr) == 0)
		return 0;

	if (errno == EINPROGRESS) {
		fd_set wfds;
		struct timeval tv;
		int nfds;
		struct sockaddr peer;
		socklen_t errlen, peerlen;
		int err;

		/* Wait for the connection to complete. */
		FD_ZERO(&wfds);
		FD_SET(h->fd, &wfds);
		tv.tv_sec = srvp->timeout;
		tv.tv_usec = 0;
		nfds = select(h->fd + 1, NULL, &wfds, NULL, &tv);
		if (nfds == -1) {
			generr(h, "select: %s", strerror(errno));
			close(h->fd);
			h->fd = -1;
			return -1;
		}
		if (nfds == 0) {
			generr(h, "connect: timed out");
			close(h->fd);
			h->fd = -1;
			return -1;
		}

		/* See whether we are connected now. */
		peerlen = sizeof peer;
		if (getpeername(h->fd, &peer, &peerlen) == 0)
			return 0;

		if (errno != ENOTCONN) {
			generr(h, "getpeername: %s", strerror(errno));
			close(h->fd);
			h->fd = -1;
			return -1;
		}

		/* Find out why the connect failed. */
		errlen = sizeof err;
		getsockopt(h->fd, SOL_SOCKET, SO_ERROR, &err, &errlen);
		errno = err;
	}
	generr(h, "connect: %s", strerror(errno));
	close(h->fd);
	h->fd = -1;
	return -1;
}