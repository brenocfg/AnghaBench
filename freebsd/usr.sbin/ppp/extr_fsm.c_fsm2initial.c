#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fsm {scalar_t__ state; int /*<<< orphan*/  StoppedTimer; int /*<<< orphan*/  OpenTimer; int /*<<< orphan*/  FsmTimer; } ;

/* Variables and functions */
 scalar_t__ ST_INITIAL ; 
 scalar_t__ ST_STOPPED ; 
 int /*<<< orphan*/  fsm_Close (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Down (struct fsm*) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

void
fsm2initial(struct fsm *fp)
{
  timer_Stop(&fp->FsmTimer);
  timer_Stop(&fp->OpenTimer);
  timer_Stop(&fp->StoppedTimer);
  if (fp->state == ST_STOPPED)
    fsm_Close(fp);
  if (fp->state > ST_INITIAL)
    fsm_Down(fp);
  if (fp->state > ST_INITIAL)
    fsm_Close(fp);
}