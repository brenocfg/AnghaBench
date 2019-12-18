#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ar_stat; int /*<<< orphan*/  ar_verf; } ;
struct TYPE_6__ {int /*<<< orphan*/  rp_stat; } ;
struct rpc_msg {TYPE_2__ acpted_rply; TYPE_1__ rm_reply; int /*<<< orphan*/  rm_direction; } ;
struct TYPE_8__ {int /*<<< orphan*/  xp_verf; } ;
typedef  TYPE_3__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ACCEPTED ; 
 int /*<<< orphan*/  PROC_UNAVAIL ; 
 int /*<<< orphan*/  REPLY ; 
 int /*<<< orphan*/  SVC_REPLY (TYPE_3__*,struct rpc_msg*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
svcerr_noproc(SVCXPRT *xprt)
{
	struct rpc_msg rply;

	assert(xprt != NULL);

	rply.rm_direction = REPLY;
	rply.rm_reply.rp_stat = MSG_ACCEPTED;
	rply.acpted_rply.ar_verf = xprt->xp_verf;
	rply.acpted_rply.ar_stat = PROC_UNAVAIL;
	SVC_REPLY(xprt, &rply);
}