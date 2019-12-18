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
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct thread* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct thread* TAILQ_NEXT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  td_slpq ; 
 int /*<<< orphan*/  thread_cow_free (struct thread*) ; 
 int /*<<< orphan*/  thread_free (struct thread*) ; 
 int /*<<< orphan*/  zombie_lock ; 
 int /*<<< orphan*/  zombie_threads ; 

void
thread_reap(void)
{
	struct thread *td_first, *td_next;

	/*
	 * Don't even bother to lock if none at this instant,
	 * we really don't care about the next instant.
	 */
	if (!TAILQ_EMPTY(&zombie_threads)) {
		mtx_lock_spin(&zombie_lock);
		td_first = TAILQ_FIRST(&zombie_threads);
		if (td_first)
			TAILQ_INIT(&zombie_threads);
		mtx_unlock_spin(&zombie_lock);
		while (td_first) {
			td_next = TAILQ_NEXT(td_first, td_slpq);
			thread_cow_free(td_first);
			thread_free(td_first);
			td_first = td_next;
		}
	}
}