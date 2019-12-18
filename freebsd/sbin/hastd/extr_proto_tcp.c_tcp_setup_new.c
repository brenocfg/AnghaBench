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
struct TYPE_2__ {scalar_t__ ss_family; } ;
struct tcp_ctx {int tc_fd; int tc_side; int /*<<< orphan*/  tc_magic; TYPE_1__ tc_sa; } ;
typedef  int /*<<< orphan*/  nodelay ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  PROTO_TCP_DEFAULT_PORT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_CTX_MAGIC ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int TCP_SIDE_CLIENT ; 
 int TCP_SIDE_SERVER_LISTEN ; 
 int errno ; 
 int /*<<< orphan*/  free (struct tcp_ctx*) ; 
 struct tcp_ctx* malloc (int) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcp_addr (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
tcp_setup_new(const char *addr, int side, void **ctxp)
{
	struct tcp_ctx *tctx;
	int ret, nodelay;

	PJDLOG_ASSERT(addr != NULL);
	PJDLOG_ASSERT(side == TCP_SIDE_CLIENT ||
	    side == TCP_SIDE_SERVER_LISTEN);
	PJDLOG_ASSERT(ctxp != NULL);

	tctx = malloc(sizeof(*tctx));
	if (tctx == NULL)
		return (errno);

	/* Parse given address. */
	if ((ret = tcp_addr(addr, PROTO_TCP_DEFAULT_PORT, &tctx->tc_sa)) != 0) {
		free(tctx);
		return (ret);
	}

	PJDLOG_ASSERT(tctx->tc_sa.ss_family != AF_UNSPEC);

	tctx->tc_fd = socket(tctx->tc_sa.ss_family, SOCK_STREAM, 0);
	if (tctx->tc_fd == -1) {
		ret = errno;
		free(tctx);
		return (ret);
	}

	PJDLOG_ASSERT(tctx->tc_sa.ss_family != AF_UNSPEC);

	/* Socket settings. */
	nodelay = 1;
	if (setsockopt(tctx->tc_fd, IPPROTO_TCP, TCP_NODELAY, &nodelay,
	    sizeof(nodelay)) == -1) {
		pjdlog_errno(LOG_WARNING, "Unable to set TCP_NOELAY");
	}

	tctx->tc_side = side;
	tctx->tc_magic = TCP_CTX_MAGIC;
	*ctxp = tctx;

	return (0);
}