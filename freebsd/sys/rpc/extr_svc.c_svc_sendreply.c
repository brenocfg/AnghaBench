#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* xdrproc_t ) (int /*<<< orphan*/ *,void*) ;
struct svc_req {int /*<<< orphan*/  rq_verf; int /*<<< orphan*/  rq_xid; } ;
struct TYPE_5__ {scalar_t__ (* proc ) (int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/ * where; } ;
struct TYPE_6__ {TYPE_2__ ar_results; int /*<<< orphan*/  ar_stat; int /*<<< orphan*/  ar_verf; } ;
struct TYPE_4__ {int /*<<< orphan*/  rp_stat; } ;
struct rpc_msg {TYPE_3__ acpted_rply; TYPE_1__ rm_reply; int /*<<< orphan*/  rm_direction; int /*<<< orphan*/  rm_xid; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MSG_ACCEPTED ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  REPLY ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svc_sendreply_common (struct svc_req*,struct rpc_msg*,struct mbuf*) ; 
 scalar_t__ xdr_void ; 
 int /*<<< orphan*/  xdrmbuf_create (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 

bool_t
svc_sendreply(struct svc_req *rqstp, xdrproc_t xdr_results, void * xdr_location)
{
	struct rpc_msg rply; 
	struct mbuf *m;
	XDR xdrs;
	bool_t ok;

	rply.rm_xid = rqstp->rq_xid;
	rply.rm_direction = REPLY;  
	rply.rm_reply.rp_stat = MSG_ACCEPTED; 
	rply.acpted_rply.ar_verf = rqstp->rq_verf; 
	rply.acpted_rply.ar_stat = SUCCESS;
	rply.acpted_rply.ar_results.where = NULL;
	rply.acpted_rply.ar_results.proc = (xdrproc_t) xdr_void;

	m = m_getcl(M_WAITOK, MT_DATA, 0);
	xdrmbuf_create(&xdrs, m, XDR_ENCODE);
	ok = xdr_results(&xdrs, xdr_location);
	XDR_DESTROY(&xdrs);

	if (ok) {
		return (svc_sendreply_common(rqstp, &rply, m));
	} else {
		m_freem(m);
		return (FALSE);
	}
}