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
struct thread {struct proc* td_proc; } ;
struct proc {int p_flag; } ;

/* Variables and functions */
 struct thread* FIRST_THREAD_IN_PROC (struct proc*) ; 
 struct proc* LIST_NEXT (struct proc*,int /*<<< orphan*/ ) ; 
 int P_INMEM ; 
 struct thread* TAILQ_NEXT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_list ; 
 int /*<<< orphan*/  td_plist ; 

struct thread *
kdb_thr_next(struct thread *thr)
{
	struct proc *p;

	p = thr->td_proc;
	thr = TAILQ_NEXT(thr, td_plist);
	do {
		if (thr != NULL)
			return (thr);
		p = LIST_NEXT(p, p_list);
		if (p != NULL && (p->p_flag & P_INMEM))
			thr = FIRST_THREAD_IN_PROC(p);
	} while (p != NULL);
	return (NULL);
}