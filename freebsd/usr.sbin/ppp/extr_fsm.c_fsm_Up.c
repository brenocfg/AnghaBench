#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsm {int state; TYPE_1__* link; int /*<<< orphan*/  LogLevel; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSM_REQ_TIMER ; 
 int /*<<< orphan*/  FsmInitRestartCounter (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmSendConfigReq (struct fsm*) ; 
 int /*<<< orphan*/  NewState (struct fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_CLOSED ; 
#define  ST_INITIAL 129 
 int /*<<< orphan*/  ST_REQSENT ; 
#define  ST_STARTING 128 
 int /*<<< orphan*/  State2Nam (int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void
fsm_Up(struct fsm *fp)
{
  switch (fp->state) {
  case ST_INITIAL:
    log_Printf(fp->LogLevel, "FSM: Using \"%s\" as a transport\n",
              fp->link->name);
    NewState(fp, ST_CLOSED);
    break;
  case ST_STARTING:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    break;
  default:
    log_Printf(fp->LogLevel, "%s: Oops, Up at %s\n",
              fp->link->name, State2Nam(fp->state));
    break;
  }
}