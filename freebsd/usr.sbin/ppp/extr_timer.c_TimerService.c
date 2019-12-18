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
typedef  scalar_t__ time_t ;
struct pppTimer {scalar_t__ rest; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;struct pppTimer* enext; struct pppTimer* next; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 struct pppTimer* ExpiredList ; 
 int /*<<< orphan*/  LogTIMER ; 
 int /*<<< orphan*/  TIMER_EXPIRED ; 
 struct pppTimer* TimerList ; 
 scalar_t__ log_IsKept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_InitService (int) ; 
 int /*<<< orphan*/  timer_Show (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_TermService () ; 

__attribute__((used)) static void
TimerService(void)
{
  struct pppTimer *tp, *exp, *next;

  if (log_IsKept(LogTIMER)) {
    static time_t t;		/* Only show timers globally every second */
    time_t n = time(NULL);

    if (n > t)
      timer_Show(LogTIMER, NULL);
    t = n;
  }

  tp = TimerList;
  if (tp) {
    tp->rest = 0;

    /* Multiple timers might expire at once. Create a list of expired timers */
    exp = NULL;
    do {
      tp->state = TIMER_EXPIRED;
      next = tp->next;
      tp->enext = exp;
      exp = tp;
      tp = next;
    } while (tp && tp->rest == 0);

    TimerList = tp;
    if (TimerList != NULL)	/* Any timers remaining ? */
      timer_InitService(1);	/* Restart the Timer Service */
    else
      timer_TermService();	/* Stop the Timer Service */

    /* Process all expired timers */
    while (exp) {
      ExpiredList = exp->enext;
      exp->enext = NULL;
      if (exp->func)
        (*exp->func)(exp->arg);
      exp = ExpiredList;
    }
  }
}