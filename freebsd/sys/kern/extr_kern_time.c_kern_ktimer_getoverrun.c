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
struct thread {int /*<<< orphan*/ * td_retval; struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct itimer {int /*<<< orphan*/  it_overrun_last; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ITIMER_UNLOCK (struct itimer*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct itimer* itimer_find (struct proc*,int) ; 

int
kern_ktimer_getoverrun(struct thread *td, int timer_id)
{
	struct proc *p = td->td_proc;
	struct itimer *it;
	int error ;

	PROC_LOCK(p);
	if (timer_id < 3 ||
	    (it = itimer_find(p, timer_id)) == NULL) {
		PROC_UNLOCK(p);
		error = EINVAL;
	} else {
		td->td_retval[0] = it->it_overrun_last;
		ITIMER_UNLOCK(it);
		PROC_UNLOCK(p);
		error = 0;
	}
	return (error);
}