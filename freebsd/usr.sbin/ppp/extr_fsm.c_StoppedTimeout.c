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
struct TYPE_4__ {scalar_t__ state; } ;
struct fsm {scalar_t__ state; TYPE_2__ OpenTimer; int /*<<< orphan*/  name; TYPE_1__* link; int /*<<< orphan*/  LogLevel; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ ST_STOPPED ; 
 scalar_t__ TIMER_RUNNING ; 
 int /*<<< orphan*/  fsm2initial (struct fsm*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_2__*) ; 

__attribute__((used)) static void
StoppedTimeout(void *v)
{
  struct fsm *fp = (struct fsm *)v;

  log_Printf(fp->LogLevel, "%s: Stopped timer expired\n", fp->link->name);
  if (fp->OpenTimer.state == TIMER_RUNNING) {
    log_Printf(LogWARN, "%s: %s: aborting open delay due to stopped timer\n",
              fp->link->name, fp->name);
    timer_Stop(&fp->OpenTimer);
  }
  if (fp->state == ST_STOPPED)
    fsm2initial(fp);
}