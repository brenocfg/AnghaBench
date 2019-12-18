#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct cf_conn {int /*<<< orphan*/  verf_body; int /*<<< orphan*/  xdrs; int /*<<< orphan*/  strm_stat; } ;
struct __rpc_sockinfo {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  oa_base; } ;
struct TYPE_10__ {int xp_fd; int /*<<< orphan*/  xp_netid; scalar_t__ xp_port; TYPE_1__ xp_verf; struct cf_conn* xp_p1; } ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_IDLE ; 
 scalar_t__ __rpc_fd2sockinfo (int,struct __rpc_sockinfo*) ; 
 scalar_t__ __rpc_sockinfo2netid (struct __rpc_sockinfo*,char const**) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct cf_conn* mem_alloc (int) ; 
 int /*<<< orphan*/  read_vc ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  svc_vc_ops (TYPE_2__*) ; 
 TYPE_2__* svc_xprt_alloc () ; 
 int /*<<< orphan*/  svc_xprt_free (TYPE_2__*) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  write_vc ; 
 int /*<<< orphan*/  xdrrec_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_register (TYPE_2__*) ; 

__attribute__((used)) static SVCXPRT *
makefd_xprt(int fd, u_int sendsize, u_int recvsize)
{
	SVCXPRT *xprt;
	struct cf_conn *cd;
	const char *netid;
	struct __rpc_sockinfo si;
 
	assert(fd != -1);

	xprt = svc_xprt_alloc();
	if (xprt == NULL) {
		warnx("svc_vc: makefd_xprt: out of memory");
		goto done;
	}
	cd = mem_alloc(sizeof(struct cf_conn));
	if (cd == NULL) {
		warnx("svc_tcp: makefd_xprt: out of memory");
		svc_xprt_free(xprt);
		xprt = NULL;
		goto done;
	}
	cd->strm_stat = XPRT_IDLE;
	xdrrec_create(&(cd->xdrs), sendsize, recvsize,
	    xprt, read_vc, write_vc);
	xprt->xp_p1 = cd;
	xprt->xp_verf.oa_base = cd->verf_body;
	svc_vc_ops(xprt);  /* truly deals with calls */
	xprt->xp_port = 0;  /* this is a connection, not a rendezvouser */
	xprt->xp_fd = fd;
        if (__rpc_fd2sockinfo(fd, &si) && __rpc_sockinfo2netid(&si, &netid))
		xprt->xp_netid = strdup(netid);

	xprt_register(xprt);
done:
	return (xprt);
}