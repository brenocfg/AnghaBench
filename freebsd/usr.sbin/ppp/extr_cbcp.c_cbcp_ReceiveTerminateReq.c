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
struct physical {TYPE_2__* dl; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  phone; } ;
struct TYPE_6__ {int required; TYPE_1__ fsm; } ;
struct TYPE_5__ {TYPE_3__ cbcp; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ CBCP_ACKSENT ; 
 int /*<<< orphan*/  CBCP_CLOSED ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  cbcp_NewPhase (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cbcp_ReceiveTerminateReq(struct physical *p)
{
  if (p->dl->cbcp.fsm.state == CBCP_ACKSENT) {
    /* Don't change our state in case the peer doesn't get the ACK */
    p->dl->cbcp.required = 1;
    log_Printf(LogPHASE, "%s: CBCP: Will dial back on %s\n", p->dl->name,
               p->dl->cbcp.fsm.phone);
  } else
    cbcp_NewPhase(&p->dl->cbcp, CBCP_CLOSED);
}