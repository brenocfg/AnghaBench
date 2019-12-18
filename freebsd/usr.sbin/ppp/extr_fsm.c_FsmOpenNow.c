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
struct fsm {scalar_t__ state; TYPE_1__* parent; TYPE_2__* fn; int /*<<< orphan*/  OpenTimer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* LayerStart ) (struct fsm*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerStart ) (int /*<<< orphan*/ ,struct fsm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FSM_REQ_TIMER ; 
 int /*<<< orphan*/  FsmInitRestartCounter (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmSendConfigReq (struct fsm*) ; 
 int /*<<< orphan*/  NewState (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_REQSENT ; 
 scalar_t__ ST_STARTING ; 
 scalar_t__ ST_STOPPED ; 
 int /*<<< orphan*/  stub1 (struct fsm*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct fsm*) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
FsmOpenNow(void *v)
{
  struct fsm *fp = (struct fsm *)v;

  timer_Stop(&fp->OpenTimer);
  if (fp->state <= ST_STOPPED) {
    if (fp->state != ST_STARTING) {
      /*
       * In practice, we're only here in ST_STOPPED (when delaying the
       * first config request) or ST_CLOSED (when openmode == 0).
       *
       * The ST_STOPPED bit is breaking the RFC already :-(
       *
       * According to the RFC (1661) state transition table, a TLS isn't
       * required for an Open event when state == Closed, but the RFC
       * must be wrong as TLS hasn't yet been called (since the last TLF)
       * ie, Initial gets an `Up' event, Closing gets a RTA etc.
       */
      (*fp->fn->LayerStart)(fp);
      (*fp->parent->LayerStart)(fp->parent->object, fp);
    }
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
  }
}