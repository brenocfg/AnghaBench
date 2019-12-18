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
struct sockaddr_storage {int dummy; } ;
struct tcp_ctx {int /*<<< orphan*/  tc_fd; struct sockaddr_storage tc_sa; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  TCP_SIDE_CLIENT ; 
 int bind (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pjdlog_common (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  sockaddr_len (struct sockaddr_storage*) ; 
 int tcp_addr (char const*,int /*<<< orphan*/ ,struct sockaddr_storage*) ; 
 int /*<<< orphan*/  tcp_close (struct tcp_ctx*) ; 
 int tcp_connect_wait (struct tcp_ctx*,int) ; 
 int tcp_setup_new (char const*,int /*<<< orphan*/ ,struct tcp_ctx**) ; 

__attribute__((used)) static int
tcp_connect(const char *srcaddr, const char *dstaddr, int timeout, void **ctxp)
{
	struct tcp_ctx *tctx;
	struct sockaddr_storage sa;
	int error, flags, ret;

	PJDLOG_ASSERT(srcaddr == NULL || srcaddr[0] != '\0');
	PJDLOG_ASSERT(dstaddr != NULL);
	PJDLOG_ASSERT(timeout >= -1);

	error = tcp_setup_new(dstaddr, TCP_SIDE_CLIENT, &tctx);
	if (error != 0)
		return (error);
	if (srcaddr != NULL) {
		error = tcp_addr(srcaddr, 0, &sa);
		if (error != 0)
			goto fail;
		if (bind(tctx->tc_fd, (struct sockaddr *)&sa,
		    sockaddr_len(&sa)) == -1) {
			error = errno;
			goto fail;
		}
	}

	flags = fcntl(tctx->tc_fd, F_GETFL);
	if (flags == -1) {
		error = errno;
		pjdlog_common(LOG_DEBUG, 1, errno, "fcntl(F_GETFL) failed");
		goto fail;
	}
	/*
	 * We make socket non-blocking so we can handle connection timeout
	 * manually.
	 */
	flags |= O_NONBLOCK;
	if (fcntl(tctx->tc_fd, F_SETFL, flags) == -1) {
		error = errno;
		pjdlog_common(LOG_DEBUG, 1, errno,
		    "fcntl(F_SETFL, O_NONBLOCK) failed");
		goto fail;
	}

	ret = connect(tctx->tc_fd, (struct sockaddr *)&tctx->tc_sa,
	    sockaddr_len(&tctx->tc_sa));
	if (ret == -1 && errno != EINPROGRESS) {
		error = errno;
		pjdlog_common(LOG_DEBUG, 1, errno, "connect() failed");
		goto fail;
	}

	if (timeout >= 0) {
		if (ret == -1) {
			/* Connection still in progress. Wait for it. */
			error = tcp_connect_wait(tctx, timeout);
			if (error != 0)
				goto fail;
		} else {
			/* Connection already complete. */
			flags &= ~O_NONBLOCK;
			if (fcntl(tctx->tc_fd, F_SETFL, flags) == -1) {
				error = errno;
				pjdlog_common(LOG_DEBUG, 1, errno,
				    "fcntl(F_SETFL, ~O_NONBLOCK) failed");
				goto fail;
			}
		}
	}

	*ctxp = tctx;
	return (0);
fail:
	tcp_close(tctx);
	return (error);
}