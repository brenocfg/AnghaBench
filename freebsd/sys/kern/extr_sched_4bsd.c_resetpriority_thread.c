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
struct thread {scalar_t__ td_priority; int /*<<< orphan*/  td_user_pri; } ;

/* Variables and functions */
 scalar_t__ PRI_MAX_TIMESHARE ; 
 scalar_t__ PRI_MIN_TIMESHARE ; 
 int /*<<< orphan*/  maybe_resched (struct thread*) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resetpriority_thread(struct thread *td)
{

	/* Only change threads with a time sharing user priority. */
	if (td->td_priority < PRI_MIN_TIMESHARE ||
	    td->td_priority > PRI_MAX_TIMESHARE)
		return;

	/* XXX the whole needresched thing is broken, but not silly. */
	maybe_resched(td);

	sched_prio(td, td->td_user_pri);
}