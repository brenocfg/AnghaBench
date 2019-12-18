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
struct fsm {int state; TYPE_2__* parent; TYPE_1__* fn; } ;
struct TYPE_4__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerDown ) (int /*<<< orphan*/ ,struct fsm*) ;int /*<<< orphan*/  (* LayerStart ) (int /*<<< orphan*/ ,struct fsm*) ;int /*<<< orphan*/  (* LayerFinish ) (int /*<<< orphan*/ ,struct fsm*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* LayerDown ) (struct fsm*) ;int /*<<< orphan*/  (* LayerStart ) (struct fsm*) ;int /*<<< orphan*/  (* LayerFinish ) (struct fsm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NewState (struct fsm*,int /*<<< orphan*/ ) ; 
#define  ST_ACKRCVD 135 
#define  ST_ACKSENT 134 
#define  ST_CLOSED 133 
#define  ST_CLOSING 132 
 int /*<<< orphan*/  ST_INITIAL ; 
#define  ST_OPENED 131 
#define  ST_REQSENT 130 
 int /*<<< orphan*/  ST_STARTING ; 
#define  ST_STOPPED 129 
#define  ST_STOPPING 128 
 int /*<<< orphan*/  stub1 (struct fsm*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct fsm*) ; 
 int /*<<< orphan*/  stub3 (struct fsm*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct fsm*) ; 
 int /*<<< orphan*/  stub5 (struct fsm*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,struct fsm*) ; 

void
fsm_Down(struct fsm *fp)
{
  switch (fp->state) {
  case ST_CLOSED:
    NewState(fp, ST_INITIAL);
    break;
  case ST_CLOSING:
    /* This TLF contradicts the RFC (1661), which ``misses it out'' ! */
    (*fp->fn->LayerFinish)(fp);
    NewState(fp, ST_INITIAL);
    (*fp->parent->LayerFinish)(fp->parent->object, fp);
    break;
  case ST_STOPPED:
    NewState(fp, ST_STARTING);
    (*fp->fn->LayerStart)(fp);
    (*fp->parent->LayerStart)(fp->parent->object, fp);
    break;
  case ST_STOPPING:
  case ST_REQSENT:
  case ST_ACKRCVD:
  case ST_ACKSENT:
    NewState(fp, ST_STARTING);
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    NewState(fp, ST_STARTING);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  }
}