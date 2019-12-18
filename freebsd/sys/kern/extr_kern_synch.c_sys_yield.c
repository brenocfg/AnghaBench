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
struct yield_args {int dummy; } ;
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_pri_class; } ;

/* Variables and functions */
 scalar_t__ PRI_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRI_MAX_TIMESHARE ; 
 scalar_t__ PRI_TIMESHARE ; 
 int SWT_RELINQUISH ; 
 int SW_VOL ; 
 int /*<<< orphan*/  mi_switch (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

int
sys_yield(struct thread *td, struct yield_args *uap)
{

	thread_lock(td);
	if (PRI_BASE(td->td_pri_class) == PRI_TIMESHARE)
		sched_prio(td, PRI_MAX_TIMESHARE);
	mi_switch(SW_VOL | SWT_RELINQUISH, NULL);
	thread_unlock(td);
	td->td_retval[0] = 0;
	return (0);
}