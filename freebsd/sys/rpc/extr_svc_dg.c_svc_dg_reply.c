#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {scalar_t__ ar_stat; } ;
struct TYPE_6__ {scalar_t__ rp_stat; TYPE_1__ rp_acpt; } ;
struct rpc_msg {TYPE_2__ rm_reply; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_7__ {int /*<<< orphan*/ * xp_p2; int /*<<< orphan*/  xp_socket; } ;
typedef  TYPE_3__ SVCXPRT ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ MSG_ACCEPTED ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  m_fixhdr (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sosend (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_replymsg (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 int /*<<< orphan*/  xdrmbuf_append (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  xdrmbuf_create (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
svc_dg_reply(SVCXPRT *xprt, struct rpc_msg *msg,
    struct sockaddr *addr, struct mbuf *m, uint32_t *seq)
{
	XDR xdrs;
	struct mbuf *mrep;
	bool_t stat = TRUE;
	int error;

	mrep = m_gethdr(M_WAITOK, MT_DATA);

	xdrmbuf_create(&xdrs, mrep, XDR_ENCODE);

	if (msg->rm_reply.rp_stat == MSG_ACCEPTED &&
	    msg->rm_reply.rp_acpt.ar_stat == SUCCESS) {
		if (!xdr_replymsg(&xdrs, msg))
			stat = FALSE;
		else
			xdrmbuf_append(&xdrs, m);
	} else {
		stat = xdr_replymsg(&xdrs, msg);
	}

	if (stat) {
		m_fixhdr(mrep);
		error = sosend(xprt->xp_socket, addr, NULL, mrep, NULL,
		    0, curthread);
		if (!error) {
			stat = TRUE;
		}
	} else {
		m_freem(mrep);
	}

	XDR_DESTROY(&xdrs);
	xprt->xp_p2 = NULL;

	return (stat);
}