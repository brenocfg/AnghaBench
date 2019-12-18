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
struct pppTimer {scalar_t__ state; scalar_t__ rest; struct pppTimer* enext; struct pppTimer* next; int /*<<< orphan*/  name; } ;
struct itimerval {int dummy; } ;

/* Variables and functions */
 struct pppTimer* ExpiredList ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  LogERROR ; 
 scalar_t__ RESTVAL (struct itimerval) ; 
 scalar_t__ TIMER_RUNNING ; 
 scalar_t__ TIMER_STOPPED ; 
 struct pppTimer* TimerList ; 
 scalar_t__ getitimer (int /*<<< orphan*/ ,struct itimerval*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_InitService (int) ; 
 int /*<<< orphan*/  timer_TermService () ; 

__attribute__((used)) static void
StopTimerNoBlock(struct pppTimer *tp)
{
  struct itimerval itimer;
  struct pppTimer *t, *pt;

  /*
   * A RUNNING timer must be removed from TimerList (->next list).
   * A STOPPED timer isn't in any list, but may have a bogus [e]next field.
   * An EXPIRED timer is in the ->enext list.
   */

  if (tp->state == TIMER_STOPPED)
    return;

  pt = NULL;
  for (t = TimerList; t != tp && t != NULL; t = t->next)
    pt = t;

  if (t) {
    if (pt)
      pt->next = t->next;
    else {
      TimerList = t->next;
      if (TimerList == NULL)	/* Last one ? */
	timer_TermService();	/* Terminate Timer Service */
    }
    if (t->next) {
      if (!pt && getitimer(ITIMER_REAL, &itimer) == 0)
        t->next->rest += RESTVAL(itimer); /* t (tp) was the first in the list */
      else
        t->next->rest += t->rest;
      if (!pt && t->next->rest > 0)   /* t->next is now the first in the list */
        timer_InitService(1);
    }
  } else {
    /* Search for any pending expired timers */
    pt = NULL;
    for (t = ExpiredList; t != tp && t != NULL; t = t->enext)
      pt = t;

    if (t) {
      if (pt)
        pt->enext = t->enext;
      else
        ExpiredList = t->enext;
    } else if (tp->state == TIMER_RUNNING)
      log_Printf(LogERROR, "Oops, %s timer not found!!\n", tp->name);
  }

  tp->next = tp->enext = NULL;
  tp->state = TIMER_STOPPED;
}