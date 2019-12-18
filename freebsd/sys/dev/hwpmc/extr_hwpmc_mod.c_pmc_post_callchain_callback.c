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
struct thread {int td_pflags; } ;

/* Variables and functions */
 int TDP_CALLCHAIN ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  sched_pin () ; 

__attribute__((used)) static void
pmc_post_callchain_callback(void)
{
	struct thread *td;

	td = curthread;

	/*
	 * If there is multiple PMCs for the same interrupt ignore new post
	 */
	if (td->td_pflags & TDP_CALLCHAIN)
		return;

	/*
	 * Mark this thread as needing callchain capture.
	 * `td->td_pflags' will be safe to touch because this thread
	 * was in user space when it was interrupted.
	 */
	td->td_pflags |= TDP_CALLCHAIN;

	/*
	 * Don't let this thread migrate between CPUs until callchain
	 * capture completes.
	 */
	sched_pin();

	return;
}