#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_7__ {int /*<<< orphan*/  proc; void* where; } ;
struct TYPE_9__ {TYPE_1__ ar_results; int /*<<< orphan*/  ar_stat; int /*<<< orphan*/  ar_verf; } ;
struct TYPE_8__ {int /*<<< orphan*/  rp_stat; } ;
struct rpc_msg {TYPE_3__ acpted_rply; TYPE_2__ rm_reply; int /*<<< orphan*/  rm_direction; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_10__ {int /*<<< orphan*/  xp_verf; } ;
typedef  TYPE_4__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ACCEPTED ; 
 int /*<<< orphan*/  REPLY ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  SVC_REPLY (TYPE_4__*,struct rpc_msg*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

bool_t
svc_sendreply(SVCXPRT *xprt, xdrproc_t xdr_results,
    void * xdr_location)
{
	struct rpc_msg rply; 

	assert(xprt != NULL);

	rply.rm_direction = REPLY;  
	rply.rm_reply.rp_stat = MSG_ACCEPTED; 
	rply.acpted_rply.ar_verf = xprt->xp_verf; 
	rply.acpted_rply.ar_stat = SUCCESS;
	rply.acpted_rply.ar_results.where = xdr_location;
	rply.acpted_rply.ar_results.proc = xdr_results;
	return (SVC_REPLY(xprt, &rply)); 
}