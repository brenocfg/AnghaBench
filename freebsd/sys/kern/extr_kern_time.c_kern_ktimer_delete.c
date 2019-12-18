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
struct thread {struct proc* td_proc; } ;
struct proc {TYPE_1__* p_itimers; } ;
struct itimer {scalar_t__ it_usecount; int /*<<< orphan*/  it_ksi; int /*<<< orphan*/  it_clockid; int /*<<< orphan*/  it_flags; int /*<<< orphan*/  it_mtx; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** its_timers; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimer*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ITF_DELETING ; 
 int /*<<< orphan*/  ITF_WANTED ; 
 int /*<<< orphan*/  ITIMER_UNLOCK (struct itimer*) ; 
 scalar_t__ KSI_ONQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PPAUSE ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct itimer* itimer_find (struct proc*,int) ; 
 int /*<<< orphan*/  itimer_zone ; 
 int /*<<< orphan*/  msleep (struct itimer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigqueue_take (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_delete ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct itimer*) ; 

int
kern_ktimer_delete(struct thread *td, int timerid)
{
	struct proc *p = td->td_proc;
	struct itimer *it;

	PROC_LOCK(p);
	it = itimer_find(p, timerid);
	if (it == NULL) {
		PROC_UNLOCK(p);
		return (EINVAL);
	}
	PROC_UNLOCK(p);

	it->it_flags |= ITF_DELETING;
	while (it->it_usecount > 0) {
		it->it_flags |= ITF_WANTED;
		msleep(it, &it->it_mtx, PPAUSE, "itimer", 0);
	}
	it->it_flags &= ~ITF_WANTED;
	CLOCK_CALL(it->it_clockid, timer_delete, (it));
	ITIMER_UNLOCK(it);

	PROC_LOCK(p);
	if (KSI_ONQ(&it->it_ksi))
		sigqueue_take(&it->it_ksi);
	p->p_itimers->its_timers[timerid] = NULL;
	PROC_UNLOCK(p);
	uma_zfree(itimer_zone, it);
	return (0);
}