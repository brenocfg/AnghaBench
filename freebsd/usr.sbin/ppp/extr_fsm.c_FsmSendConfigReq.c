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
struct TYPE_5__ {scalar_t__ reqs; } ;
struct fsm {TYPE_1__* link; int /*<<< orphan*/  name; TYPE_2__ more; int /*<<< orphan*/  FsmTimer; TYPE_3__* fn; int /*<<< orphan*/  restart; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* SendConfigReq ) (struct fsm*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  lcp; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  fsm_Close (struct fsm*) ; 
 int /*<<< orphan*/  lcp_SendIdentification (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fsm*) ; 
 int /*<<< orphan*/  timer_Start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
FsmSendConfigReq(struct fsm *fp)
{
  if (fp->more.reqs-- > 0 && fp->restart-- > 0) {
    (*fp->fn->SendConfigReq)(fp);
    timer_Start(&fp->FsmTimer);		/* Start restart timer */
  } else {
    if (fp->more.reqs < 0)
      log_Printf(LogPHASE, "%s: Too many %s REQs sent - abandoning "
                 "negotiation\n", fp->link->name, fp->name);
    lcp_SendIdentification(&fp->link->lcp);
    fsm_Close(fp);
  }
}