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
struct TYPE_2__ {int /*<<< orphan*/  ss_family; } ;
struct tcp_ctx {int tc_fd; int tc_wait_called; int /*<<< orphan*/  tc_magic; int /*<<< orphan*/  tc_side; TYPE_1__ tc_sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  TCP_CTX_MAGIC ; 
 int /*<<< orphan*/  TCP_SIDE_CLIENT ; 
 int /*<<< orphan*/  TCP_SIDE_SERVER_WORK ; 
 int errno ; 
 struct tcp_ctx* malloc (int) ; 

__attribute__((used)) static int
tcp_wrap(int fd, bool client, void **ctxp)
{
	struct tcp_ctx *tctx;

	PJDLOG_ASSERT(fd >= 0);
	PJDLOG_ASSERT(ctxp != NULL);

	tctx = malloc(sizeof(*tctx));
	if (tctx == NULL)
		return (errno);

	tctx->tc_fd = fd;
	tctx->tc_sa.ss_family = AF_UNSPEC;
	tctx->tc_wait_called = (client ? false : true);
	tctx->tc_side = (client ? TCP_SIDE_CLIENT : TCP_SIDE_SERVER_WORK);
	tctx->tc_magic = TCP_CTX_MAGIC;
	*ctxp = tctx;

	return (0);
}