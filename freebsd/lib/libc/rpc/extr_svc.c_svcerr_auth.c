#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rj_why; int /*<<< orphan*/  rj_stat; } ;
struct TYPE_3__ {int /*<<< orphan*/  rp_stat; } ;
struct rpc_msg {TYPE_2__ rjcted_rply; TYPE_1__ rm_reply; int /*<<< orphan*/  rm_direction; } ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_ERROR ; 
 int /*<<< orphan*/  MSG_DENIED ; 
 int /*<<< orphan*/  REPLY ; 
 int /*<<< orphan*/  SVC_REPLY (int /*<<< orphan*/ *,struct rpc_msg*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
svcerr_auth(SVCXPRT *xprt, enum auth_stat why)
{
	struct rpc_msg rply;

	assert(xprt != NULL);

	rply.rm_direction = REPLY;
	rply.rm_reply.rp_stat = MSG_DENIED;
	rply.rjcted_rply.rj_stat = AUTH_ERROR;
	rply.rjcted_rply.rj_why = why;
	SVC_REPLY(xprt, &rply);
}