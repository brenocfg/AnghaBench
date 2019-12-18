#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct TYPE_2__ {scalar_t__ ss_family; int /*<<< orphan*/  ss_len; } ;
struct tcp_ctx {int /*<<< orphan*/  tc_fd; TYPE_1__ tc_sa; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TCP_SIDE_SERVER_LISTEN ; 
 int bind (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int listen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  tcp_close (struct tcp_ctx*) ; 
 int tcp_setup_new (char const*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int
tcp_server(const char *addr, void **ctxp)
{
	struct tcp_ctx *tctx;
	int ret, val;

	ret = tcp_setup_new(addr, TCP_SIDE_SERVER_LISTEN, ctxp);
	if (ret != 0)
		return (ret);

	tctx = *ctxp;

	val = 1;
	/* Ignore failure. */
	(void)setsockopt(tctx->tc_fd, SOL_SOCKET, SO_REUSEADDR, &val,
	   sizeof(val));

	PJDLOG_ASSERT(tctx->tc_sa.ss_family != AF_UNSPEC);

	if (bind(tctx->tc_fd, (struct sockaddr *)&tctx->tc_sa,
	    tctx->tc_sa.ss_len) == -1) {
		ret = errno;
		tcp_close(tctx);
		return (ret);
	}
	if (listen(tctx->tc_fd, 8) == -1) {
		ret = errno;
		tcp_close(tctx);
		return (ret);
	}

	return (0);
}