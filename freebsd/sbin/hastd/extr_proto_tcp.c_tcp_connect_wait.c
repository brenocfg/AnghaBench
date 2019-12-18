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
struct tcp_ctx {scalar_t__ tc_magic; scalar_t__ tc_side; scalar_t__ tc_fd; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  error ;

/* Variables and functions */
 int EINTR ; 
 int ETIMEDOUT ; 
 int FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 scalar_t__ TCP_CTX_MAGIC ; 
 scalar_t__ TCP_SIDE_CLIENT ; 
 int errno ; 
 int fcntl (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  pjdlog_common (int /*<<< orphan*/ ,int,int,char*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
tcp_connect_wait(void *ctx, int timeout)
{
	struct tcp_ctx *tctx = ctx;
	struct timeval tv;
	fd_set fdset;
	socklen_t esize;
	int error, flags, ret;

	PJDLOG_ASSERT(tctx != NULL);
	PJDLOG_ASSERT(tctx->tc_magic == TCP_CTX_MAGIC);
	PJDLOG_ASSERT(tctx->tc_side == TCP_SIDE_CLIENT);
	PJDLOG_ASSERT(tctx->tc_fd >= 0);
	PJDLOG_ASSERT(timeout >= 0);

	tv.tv_sec = timeout;
	tv.tv_usec = 0;
again:
	FD_ZERO(&fdset);
	FD_SET(tctx->tc_fd, &fdset);
	ret = select(tctx->tc_fd + 1, NULL, &fdset, NULL, &tv);
	if (ret == 0) {
		error = ETIMEDOUT;
		goto done;
	} else if (ret == -1) {
		if (errno == EINTR)
			goto again;
		error = errno;
		pjdlog_common(LOG_DEBUG, 1, errno, "select() failed");
		goto done;
	}
	PJDLOG_ASSERT(ret > 0);
	PJDLOG_ASSERT(FD_ISSET(tctx->tc_fd, &fdset));
	esize = sizeof(error);
	if (getsockopt(tctx->tc_fd, SOL_SOCKET, SO_ERROR, &error,
	    &esize) == -1) {
		error = errno;
		pjdlog_common(LOG_DEBUG, 1, errno,
		    "getsockopt(SO_ERROR) failed");
		goto done;
	}
	if (error != 0) {
		pjdlog_common(LOG_DEBUG, 1, error,
		    "getsockopt(SO_ERROR) returned error");
		goto done;
	}
	error = 0;
done:
	flags = fcntl(tctx->tc_fd, F_GETFL);
	if (flags == -1) {
		if (error == 0)
			error = errno;
		pjdlog_common(LOG_DEBUG, 1, errno, "fcntl(F_GETFL) failed");
		return (error);
	}
	flags &= ~O_NONBLOCK;
	if (fcntl(tctx->tc_fd, F_SETFL, flags) == -1) {
		if (error == 0)
			error = errno;
		pjdlog_common(LOG_DEBUG, 1, errno,
		    "fcntl(F_SETFL, ~O_NONBLOCK) failed");
	}
	return (error);
}