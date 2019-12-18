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
struct proc {struct itimers* p_itimers; } ;
struct itimers {struct itimer** its_timers; } ;
struct itimer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * event_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CALL (int,int /*<<< orphan*/ ,struct proc*) ; 
 int ITIMER_EV_EXEC ; 
 int ITIMER_EV_EXIT ; 
 int MAX_CLOCKS ; 
 int /*<<< orphan*/  M_SUBPROC ; 
 int TIMER_MAX ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  event_hook ; 
 int /*<<< orphan*/  free (struct itimers*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_ktimer_delete (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* posix_clocks ; 

__attribute__((used)) static void
itimers_event_hook_exit(void *arg, struct proc *p)
{
	struct itimers *its;
	struct itimer *it;
	int event = (int)(intptr_t)arg;
	int i;

	if (p->p_itimers != NULL) {
		its = p->p_itimers;
		for (i = 0; i < MAX_CLOCKS; ++i) {
			if (posix_clocks[i].event_hook != NULL)
				CLOCK_CALL(i, event_hook, (p, i, event));
		}
		/*
		 * According to susv3, XSI interval timers should be inherited
		 * by new image.
		 */
		if (event == ITIMER_EV_EXEC)
			i = 3;
		else if (event == ITIMER_EV_EXIT)
			i = 0;
		else
			panic("unhandled event");
		for (; i < TIMER_MAX; ++i) {
			if ((it = its->its_timers[i]) != NULL)
				kern_ktimer_delete(curthread, i);
		}
		if (its->its_timers[0] == NULL &&
		    its->its_timers[1] == NULL &&
		    its->its_timers[2] == NULL) {
			free(its, M_SUBPROC);
			p->p_itimers = NULL;
		}
	}
}