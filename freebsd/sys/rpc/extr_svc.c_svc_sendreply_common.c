#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int /*<<< orphan*/ * rq_addr; int /*<<< orphan*/  rq_reply_seq; int /*<<< orphan*/  rq_auth; int /*<<< orphan*/ * rq_args; TYPE_2__* rq_xprt; } ;
struct rpc_msg {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {TYPE_1__* xp_pool; } ;
struct TYPE_4__ {scalar_t__ sp_rcache; } ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  SVCAUTH_WRAP (int /*<<< orphan*/ *,struct mbuf**) ; 
 int /*<<< orphan*/  SVC_REPLY (TYPE_2__*,struct rpc_msg*,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replay_setreply (scalar_t__,struct rpc_msg*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  svc_getrpccaller (struct svc_req*) ; 

__attribute__((used)) static bool_t
svc_sendreply_common(struct svc_req *rqstp, struct rpc_msg *rply,
    struct mbuf *body)
{
	SVCXPRT *xprt = rqstp->rq_xprt;
	bool_t ok;

	if (rqstp->rq_args) {
		m_freem(rqstp->rq_args);
		rqstp->rq_args = NULL;
	}

	if (xprt->xp_pool->sp_rcache)
		replay_setreply(xprt->xp_pool->sp_rcache,
		    rply, svc_getrpccaller(rqstp), body);

	if (!SVCAUTH_WRAP(&rqstp->rq_auth, &body))
		return (FALSE);

	ok = SVC_REPLY(xprt, rply, rqstp->rq_addr, body, &rqstp->rq_reply_seq);
	if (rqstp->rq_addr) {
		free(rqstp->rq_addr, M_SONAME);
		rqstp->rq_addr = NULL;
	}

	return (ok);
}