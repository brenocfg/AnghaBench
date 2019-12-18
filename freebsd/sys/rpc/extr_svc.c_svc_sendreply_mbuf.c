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
typedef  scalar_t__ xdrproc_t ;
struct svc_req {int /*<<< orphan*/  rq_verf; int /*<<< orphan*/  rq_xid; } ;
struct TYPE_4__ {scalar_t__ proc; int /*<<< orphan*/ * where; } ;
struct TYPE_6__ {TYPE_1__ ar_results; int /*<<< orphan*/  ar_stat; int /*<<< orphan*/  ar_verf; } ;
struct TYPE_5__ {int /*<<< orphan*/  rp_stat; } ;
struct rpc_msg {TYPE_3__ acpted_rply; TYPE_2__ rm_reply; int /*<<< orphan*/  rm_direction; int /*<<< orphan*/  rm_xid; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ACCEPTED ; 
 int /*<<< orphan*/  REPLY ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  svc_sendreply_common (struct svc_req*,struct rpc_msg*,struct mbuf*) ; 
 scalar_t__ xdr_void ; 

bool_t
svc_sendreply_mbuf(struct svc_req *rqstp, struct mbuf *m)
{
	struct rpc_msg rply; 

	rply.rm_xid = rqstp->rq_xid;
	rply.rm_direction = REPLY;  
	rply.rm_reply.rp_stat = MSG_ACCEPTED; 
	rply.acpted_rply.ar_verf = rqstp->rq_verf; 
	rply.acpted_rply.ar_stat = SUCCESS;
	rply.acpted_rply.ar_results.where = NULL;
	rply.acpted_rply.ar_results.proc = (xdrproc_t) xdr_void;

	return (svc_sendreply_common(rqstp, &rply, m));
}