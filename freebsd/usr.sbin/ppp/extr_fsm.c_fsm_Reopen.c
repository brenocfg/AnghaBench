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
struct fsm {scalar_t__ state; TYPE_2__* parent; TYPE_1__* fn; } ;
struct TYPE_4__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerDown ) (int /*<<< orphan*/ ,struct fsm*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* LayerDown ) (struct fsm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FSM_REQ_TIMER ; 
 int /*<<< orphan*/  FsmInitRestartCounter (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmSendConfigReq (struct fsm*) ; 
 int /*<<< orphan*/  NewState (struct fsm*,int /*<<< orphan*/ ) ; 
 scalar_t__ ST_OPENED ; 
 int /*<<< orphan*/  ST_REQSENT ; 
 int /*<<< orphan*/  stub1 (struct fsm*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct fsm*) ; 

void
fsm_Reopen(struct fsm *fp)
{
  if (fp->state == ST_OPENED) {
    (*fp->fn->LayerDown)(fp);
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
  }
}