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
struct proc {scalar_t__ p_state; scalar_t__ p_pid; } ;
typedef  scalar_t__ fixpt_t ;

/* Variables and functions */
#define  BOTH 130 
#define  ONLYA 129 
#define  ONLYB 128 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ PRS_ZOMBIE ; 
 int TESTAB (int,int) ; 
 int proc_sum (struct proc*,scalar_t__*) ; 

__attribute__((used)) static int
proc_compare(struct proc *p1, struct proc *p2)
{

	int runa, runb;
	fixpt_t esta, estb;

	if (p1 == NULL)
		return (1);

	/*
	 * Fetch various stats about these processes.  After we drop the
	 * lock the information could be stale but the race is unimportant.
	 */
	PROC_LOCK(p1);
	runa = proc_sum(p1, &esta);
	PROC_UNLOCK(p1);
	PROC_LOCK(p2);
	runb = proc_sum(p2, &estb);
	PROC_UNLOCK(p2);

	/*
	 * see if at least one of them is runnable
	 */
	switch (TESTAB(runa, runb)) {
	case ONLYA:
		return (0);
	case ONLYB:
		return (1);
	case BOTH:
		break;
	}
	/*
	 *  favor one with highest recent cpu utilization
	 */
	if (estb > esta)
		return (1);
	if (esta > estb)
		return (0);
	/*
	 * weed out zombies
	 */
	switch (TESTAB(p1->p_state == PRS_ZOMBIE, p2->p_state == PRS_ZOMBIE)) {
	case ONLYA:
		return (1);
	case ONLYB:
		return (0);
	case BOTH:
		break;
	}

	return (p2->p_pid > p1->p_pid);		/* tie - return highest pid */
}