#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct rpc_msg {int dummy; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ct_data {int /*<<< orphan*/  ct_lock; } ;
struct cf_conn {struct mbuf* mreq; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_4__ {int /*<<< orphan*/  xp_lock; scalar_t__ xp_p2; scalar_t__ xp_p1; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_callmsg (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 int /*<<< orphan*/  xdrmbuf_create (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* xdrmbuf_getall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_inactive_self (TYPE_1__*) ; 

__attribute__((used)) static bool_t
svc_vc_backchannel_recv(SVCXPRT *xprt, struct rpc_msg *msg,
    struct sockaddr **addrp, struct mbuf **mp)
{
	struct cf_conn *cd = (struct cf_conn *) xprt->xp_p1;
	struct ct_data *ct;
	struct mbuf *m;
	XDR xdrs;

	sx_xlock(&xprt->xp_lock);
	ct = (struct ct_data *)xprt->xp_p2;
	if (ct == NULL) {
		sx_xunlock(&xprt->xp_lock);
		return (FALSE);
	}
	mtx_lock(&ct->ct_lock);
	m = cd->mreq;
	if (m == NULL) {
		xprt_inactive_self(xprt);
		mtx_unlock(&ct->ct_lock);
		sx_xunlock(&xprt->xp_lock);
		return (FALSE);
	}
	cd->mreq = m->m_nextpkt;
	mtx_unlock(&ct->ct_lock);
	sx_xunlock(&xprt->xp_lock);

	xdrmbuf_create(&xdrs, m, XDR_DECODE);
	if (! xdr_callmsg(&xdrs, msg)) {
		XDR_DESTROY(&xdrs);
		return (FALSE);
	}
	*addrp = NULL;
	*mp = xdrmbuf_getall(&xdrs);
	XDR_DESTROY(&xdrs);
	return (TRUE);
}