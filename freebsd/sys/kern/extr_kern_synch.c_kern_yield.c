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
struct thread {int td_user_pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_GIANT () ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 int PRI_USER ; 
 int SWT_RELINQUISH ; 
 int SW_VOL ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mi_switch (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
kern_yield(int prio)
{
	struct thread *td;

	td = curthread;
	DROP_GIANT();
	thread_lock(td);
	if (prio == PRI_USER)
		prio = td->td_user_pri;
	if (prio >= 0)
		sched_prio(td, prio);
	mi_switch(SW_VOL | SWT_RELINQUISH, NULL);
	thread_unlock(td);
	PICKUP_GIANT();
}