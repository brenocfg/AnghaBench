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
struct thread {int /*<<< orphan*/  td_user_pri; int /*<<< orphan*/  td_base_pri; int /*<<< orphan*/  td_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDQ_SELF () ; 
 int /*<<< orphan*/  tdq_setlowpri (int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
sched_userret_slowpath(struct thread *td)
{

	thread_lock(td);
	td->td_priority = td->td_user_pri;
	td->td_base_pri = td->td_user_pri;
	tdq_setlowpri(TDQ_SELF(), td);
	thread_unlock(td);
}