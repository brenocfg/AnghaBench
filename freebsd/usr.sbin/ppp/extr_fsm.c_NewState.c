#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; void* arg; int /*<<< orphan*/  func; scalar_t__ load; } ;
struct fsm {int state; TYPE_2__ StoppedTimer; TYPE_2__ FsmTimer; TYPE_1__* link; int /*<<< orphan*/  LogLevel; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ST_INITIAL ; 
 int ST_OPENED ; 
 int ST_STOPPED ; 
 int /*<<< orphan*/  State2Nam (int) ; 
 int /*<<< orphan*/  StoppedTimeout ; 
 scalar_t__ TIMER_RUNNING ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_Start (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_2__*) ; 

__attribute__((used)) static void
NewState(struct fsm *fp, int new)
{
  log_Printf(fp->LogLevel, "%s: State change %s --> %s\n",
             fp->link->name, State2Nam(fp->state), State2Nam(new));
  if (fp->state == ST_STOPPED && fp->StoppedTimer.state == TIMER_RUNNING)
    timer_Stop(&fp->StoppedTimer);
  fp->state = new;
  if ((new >= ST_INITIAL && new <= ST_STOPPED) || (new == ST_OPENED)) {
    timer_Stop(&fp->FsmTimer);
    if (new == ST_STOPPED && fp->StoppedTimer.load) {
      timer_Stop(&fp->StoppedTimer);
      fp->StoppedTimer.func = StoppedTimeout;
      fp->StoppedTimer.arg = (void *) fp;
      timer_Start(&fp->StoppedTimer);
    }
  }
}