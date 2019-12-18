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
struct fsm {int state; TYPE_2__* parent; TYPE_1__* fn; int /*<<< orphan*/  FsmTimer; scalar_t__ restart; } ;
struct TYPE_4__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerFinish ) (int /*<<< orphan*/ ,struct fsm*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* LayerFinish ) (struct fsm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FsmSendConfigReq (struct fsm*) ; 
 int /*<<< orphan*/  FsmSendTerminateReq (struct fsm*) ; 
 int /*<<< orphan*/  NewState (struct fsm*,int const) ; 
#define  ST_ACKRCVD 132 
#define  ST_ACKSENT 131 
 int const ST_CLOSED ; 
#define  ST_CLOSING 130 
#define  ST_REQSENT 129 
 int const ST_STOPPED ; 
#define  ST_STOPPING 128 
 int /*<<< orphan*/  stub1 (struct fsm*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct fsm*) ; 
 int /*<<< orphan*/  stub3 (struct fsm*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct fsm*) ; 
 int /*<<< orphan*/  stub5 (struct fsm*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,struct fsm*) ; 
 int /*<<< orphan*/  timer_Start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
FsmTimeout(void *v)
{
  struct fsm *fp = (struct fsm *)v;

  if (fp->restart) {
    switch (fp->state) {
    case ST_CLOSING:
    case ST_STOPPING:
      FsmSendTerminateReq(fp);
      break;
    case ST_REQSENT:
    case ST_ACKSENT:
      FsmSendConfigReq(fp);
      break;
    case ST_ACKRCVD:
      FsmSendConfigReq(fp);
      NewState(fp, ST_REQSENT);
      break;
    }
    timer_Start(&fp->FsmTimer);
  } else {
    switch (fp->state) {
    case ST_CLOSING:
      (*fp->fn->LayerFinish)(fp);
      NewState(fp, ST_CLOSED);
      (*fp->parent->LayerFinish)(fp->parent->object, fp);
      break;
    case ST_STOPPING:
      (*fp->fn->LayerFinish)(fp);
      NewState(fp, ST_STOPPED);
      (*fp->parent->LayerFinish)(fp->parent->object, fp);
      break;
    case ST_REQSENT:		/* XXX: 3p */
    case ST_ACKSENT:
    case ST_ACKRCVD:
      (*fp->fn->LayerFinish)(fp);
      NewState(fp, ST_STOPPED);
      (*fp->parent->LayerFinish)(fp->parent->object, fp);
      break;
    }
  }
}