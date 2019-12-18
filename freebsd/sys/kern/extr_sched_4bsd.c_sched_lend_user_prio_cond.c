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
typedef  int /*<<< orphan*/  u_char ;
struct thread {scalar_t__ td_user_pri; scalar_t__ td_priority; int /*<<< orphan*/  td_base_user_pri; int /*<<< orphan*/  td_lend_user_pri; } ;

/* Variables and functions */
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_lend_user_prio (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
sched_lend_user_prio_cond(struct thread *td, u_char prio)
{

	if (td->td_lend_user_pri != prio)
		goto lend;
	if (td->td_user_pri != min(prio, td->td_base_user_pri))
		goto lend;
	if (td->td_priority >= td->td_user_pri)
		goto lend;
	return;

lend:
	thread_lock(td);
	sched_lend_user_prio(td, prio);
	thread_unlock(td);
}