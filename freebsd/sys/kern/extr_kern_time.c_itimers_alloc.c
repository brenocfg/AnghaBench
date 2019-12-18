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
struct proc {struct itimers* p_itimers; } ;
struct itimers {int /*<<< orphan*/ ** its_timers; int /*<<< orphan*/  its_worklist; int /*<<< orphan*/  its_prof; int /*<<< orphan*/  its_virtual; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_SUBPROC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int TIMER_MAX ; 
 int /*<<< orphan*/  free (struct itimers*,int /*<<< orphan*/ ) ; 
 struct itimers* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
itimers_alloc(struct proc *p)
{
	struct itimers *its;
	int i;

	its = malloc(sizeof (struct itimers), M_SUBPROC, M_WAITOK | M_ZERO);
	LIST_INIT(&its->its_virtual);
	LIST_INIT(&its->its_prof);
	TAILQ_INIT(&its->its_worklist);
	for (i = 0; i < TIMER_MAX; i++)
		its->its_timers[i] = NULL;
	PROC_LOCK(p);
	if (p->p_itimers == NULL) {
		p->p_itimers = its;
		PROC_UNLOCK(p);
	}
	else {
		PROC_UNLOCK(p);
		free(its, M_SUBPROC);
	}
}