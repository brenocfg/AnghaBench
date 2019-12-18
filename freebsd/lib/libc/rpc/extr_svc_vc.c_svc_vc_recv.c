#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rpc_msg {int /*<<< orphan*/  rm_xid; } ;
struct TYPE_7__ {int /*<<< orphan*/  x_op; } ;
struct cf_conn {int /*<<< orphan*/  strm_stat; int /*<<< orphan*/  x_id; scalar_t__ nonblock; TYPE_1__ xdrs; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  TYPE_1__ XDR ;
struct TYPE_8__ {scalar_t__ xp_p1; } ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XPRT_DIED ; 
 int /*<<< orphan*/  __xdrrec_getrec (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_callmsg (TYPE_1__*,struct rpc_msg*) ; 
 int /*<<< orphan*/  xdrrec_skiprecord (TYPE_1__*) ; 

__attribute__((used)) static bool_t
svc_vc_recv(SVCXPRT *xprt, struct rpc_msg *msg)
{
	struct cf_conn *cd;
	XDR *xdrs;

	assert(xprt != NULL);
	assert(msg != NULL);

	cd = (struct cf_conn *)(xprt->xp_p1);
	xdrs = &(cd->xdrs);

	if (cd->nonblock) {
		if (!__xdrrec_getrec(xdrs, &cd->strm_stat, TRUE))
			return FALSE;
	} else {
		(void)xdrrec_skiprecord(xdrs);
	}

	xdrs->x_op = XDR_DECODE;
	if (xdr_callmsg(xdrs, msg)) {
		cd->x_id = msg->rm_xid;
		return (TRUE);
	}
	cd->strm_stat = XPRT_DIED;
	return (FALSE);
}