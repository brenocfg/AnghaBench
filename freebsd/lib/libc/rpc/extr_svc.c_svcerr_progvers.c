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
typedef  void* u_int32_t ;
struct TYPE_7__ {void* high; void* low; } ;
struct TYPE_9__ {TYPE_1__ ar_vers; int /*<<< orphan*/  ar_stat; int /*<<< orphan*/  ar_verf; } ;
struct TYPE_8__ {int /*<<< orphan*/  rp_stat; } ;
struct rpc_msg {TYPE_3__ acpted_rply; TYPE_2__ rm_reply; int /*<<< orphan*/  rm_direction; } ;
typedef  scalar_t__ rpcvers_t ;
struct TYPE_10__ {int /*<<< orphan*/  xp_verf; } ;
typedef  TYPE_4__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ACCEPTED ; 
 int /*<<< orphan*/  PROG_MISMATCH ; 
 int /*<<< orphan*/  REPLY ; 
 int /*<<< orphan*/  SVC_REPLY (TYPE_4__*,struct rpc_msg*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void  
svcerr_progvers(SVCXPRT *xprt, rpcvers_t low_vers, rpcvers_t high_vers)
{
	struct rpc_msg rply;

	assert(xprt != NULL);

	rply.rm_direction = REPLY;
	rply.rm_reply.rp_stat = MSG_ACCEPTED;
	rply.acpted_rply.ar_verf = xprt->xp_verf;
	rply.acpted_rply.ar_stat = PROG_MISMATCH;
	rply.acpted_rply.ar_vers.low = (u_int32_t)low_vers;
	rply.acpted_rply.ar_vers.high = (u_int32_t)high_vers;
	SVC_REPLY(xprt, &rply);
}