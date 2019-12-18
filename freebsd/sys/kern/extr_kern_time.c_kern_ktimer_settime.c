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
struct proc {int dummy; } ;
struct itimerspec {int dummy; } ;
struct itimer {int /*<<< orphan*/  it_clockid; } ;

/* Variables and functions */
 int CLOCK_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimer*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ITIMER_UNLOCK (struct itimer*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  itimer_enter (struct itimer*) ; 
 struct itimer* itimer_find (struct proc*,int) ; 
 int /*<<< orphan*/  itimer_leave (struct itimer*) ; 
 int /*<<< orphan*/  timer_settime ; 

int
kern_ktimer_settime(struct thread *td, int timer_id, int flags,
    struct itimerspec *val, struct itimerspec *oval)
{
	struct proc *p;
	struct itimer *it;
	int error;

	p = td->td_proc;
	PROC_LOCK(p);
	if (timer_id < 3 || (it = itimer_find(p, timer_id)) == NULL) {
		PROC_UNLOCK(p);
		error = EINVAL;
	} else {
		PROC_UNLOCK(p);
		itimer_enter(it);
		error = CLOCK_CALL(it->it_clockid, timer_settime, (it,
		    flags, val, oval));
		itimer_leave(it);
		ITIMER_UNLOCK(it);
	}
	return (error);
}