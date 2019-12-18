#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; scalar_t__ buf; } ;
struct TYPE_13__ {int /*<<< orphan*/  x_op; } ;
struct svc_dg_data {int /*<<< orphan*/ * su_cache; int /*<<< orphan*/  su_xid; TYPE_1__ su_srcaddr; int /*<<< orphan*/  su_iosz; TYPE_3__ su_xdrs; } ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct rpc_msg {int /*<<< orphan*/  rm_xid; } ;
typedef  int ssize_t ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  TYPE_3__ XDR ;
struct TYPE_12__ {int len; scalar_t__ buf; } ;
struct TYPE_14__ {int xp_addrlen; int /*<<< orphan*/  xp_fd; TYPE_2__ xp_rtaddr; struct sockaddr_in xp_raddr; } ;
typedef  TYPE_4__ SVCXPRT ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_SETPOS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _sendto (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ cache_get (TYPE_4__*,struct rpc_msg*,char**,size_t*) ; 
 scalar_t__ errno ; 
 scalar_t__ mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  rpc_buffer (TYPE_4__*) ; 
 struct svc_dg_data* su_data (TYPE_4__*) ; 
 int svc_dg_recvfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_callmsg (TYPE_3__*,struct rpc_msg*) ; 

__attribute__((used)) static bool_t
svc_dg_recv(SVCXPRT *xprt, struct rpc_msg *msg)
{
	struct svc_dg_data *su = su_data(xprt);
	XDR *xdrs = &(su->su_xdrs);
	char *reply;
	struct sockaddr_storage ss;
	socklen_t alen;
	size_t replylen;
	ssize_t rlen;

again:
	alen = sizeof (struct sockaddr_storage);
	rlen = svc_dg_recvfrom(xprt->xp_fd, rpc_buffer(xprt), su->su_iosz,
	    (struct sockaddr *)(void *)&ss, &alen,
	    (struct sockaddr *)su->su_srcaddr.buf, &su->su_srcaddr.len);
	if (rlen == -1 && errno == EINTR)
		goto again;
	if (rlen == -1 || (rlen < (ssize_t)(4 * sizeof (u_int32_t))))
		return (FALSE);
	if (xprt->xp_rtaddr.len < alen) {
		if (xprt->xp_rtaddr.len != 0)
			mem_free(xprt->xp_rtaddr.buf, xprt->xp_rtaddr.len);
		xprt->xp_rtaddr.buf = mem_alloc(alen);
		xprt->xp_rtaddr.len = alen;
	}
	memcpy(xprt->xp_rtaddr.buf, &ss, alen);
#ifdef PORTMAP
	if (ss.ss_family == AF_INET) {
		xprt->xp_raddr = *(struct sockaddr_in *)xprt->xp_rtaddr.buf;
		xprt->xp_addrlen = sizeof (struct sockaddr_in);
	}
#endif				/* PORTMAP */
	xdrs->x_op = XDR_DECODE;
	XDR_SETPOS(xdrs, 0);
	if (! xdr_callmsg(xdrs, msg)) {
		return (FALSE);
	}
	su->su_xid = msg->rm_xid;
	if (su->su_cache != NULL) {
		if (cache_get(xprt, msg, &reply, &replylen)) {
			(void)_sendto(xprt->xp_fd, reply, replylen, 0,
			    (struct sockaddr *)(void *)&ss, alen);
			return (FALSE);
		}
	}
	return (TRUE);
}