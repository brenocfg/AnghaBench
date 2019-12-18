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
struct proc {int p_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct proc*,struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct proc*,int /*<<< orphan*/ ) ; 
 struct proc* LIST_NEXT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRI_USER ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_KPROC ; 
 scalar_t__ P_SHOULDSTOP (struct proc*) ; 
 scalar_t__ P_STOPPED_SINGLE ; 
 int P_SYSTEM ; 
 int P_TOTAL_STOP ; 
 int P_WEXIT ; 
 int /*<<< orphan*/  SINGLE_ALLPROC ; 
 int /*<<< orphan*/  _PHOLD (struct proc*) ; 
 int /*<<< orphan*/  _PRELE (struct proc*) ; 
 int /*<<< orphan*/  allproc ; 
 int allproc_gen ; 
 int /*<<< orphan*/  allproc_lock ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  kern_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_list ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int thread_single (struct proc*,int /*<<< orphan*/ ) ; 

void
stop_all_proc(void)
{
	struct proc *cp, *p;
	int r, gen;
	bool restart, seen_stopped, seen_exiting, stopped_some;

	cp = curproc;
allproc_loop:
	sx_xlock(&allproc_lock);
	gen = allproc_gen;
	seen_exiting = seen_stopped = stopped_some = restart = false;
	LIST_REMOVE(cp, p_list);
	LIST_INSERT_HEAD(&allproc, cp, p_list);
	for (;;) {
		p = LIST_NEXT(cp, p_list);
		if (p == NULL)
			break;
		LIST_REMOVE(cp, p_list);
		LIST_INSERT_AFTER(p, cp, p_list);
		PROC_LOCK(p);
		if ((p->p_flag & (P_KPROC | P_SYSTEM | P_TOTAL_STOP)) != 0) {
			PROC_UNLOCK(p);
			continue;
		}
		if ((p->p_flag & P_WEXIT) != 0) {
			seen_exiting = true;
			PROC_UNLOCK(p);
			continue;
		}
		if (P_SHOULDSTOP(p) == P_STOPPED_SINGLE) {
			/*
			 * Stopped processes are tolerated when there
			 * are no other processes which might continue
			 * them.  P_STOPPED_SINGLE but not
			 * P_TOTAL_STOP process still has at least one
			 * thread running.
			 */
			seen_stopped = true;
			PROC_UNLOCK(p);
			continue;
		}
		sx_xunlock(&allproc_lock);
		_PHOLD(p);
		r = thread_single(p, SINGLE_ALLPROC);
		if (r != 0)
			restart = true;
		else
			stopped_some = true;
		_PRELE(p);
		PROC_UNLOCK(p);
		sx_xlock(&allproc_lock);
	}
	/* Catch forked children we did not see in iteration. */
	if (gen != allproc_gen)
		restart = true;
	sx_xunlock(&allproc_lock);
	if (restart || stopped_some || seen_exiting || seen_stopped) {
		kern_yield(PRI_USER);
		goto allproc_loop;
	}
}