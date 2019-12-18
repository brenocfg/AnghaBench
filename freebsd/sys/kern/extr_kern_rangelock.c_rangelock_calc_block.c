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
struct rl_q_entry {int rl_q_flags; } ;
struct rangelock {struct rl_q_entry* rl_currdep; int /*<<< orphan*/  rl_waiters; } ;

/* Variables and functions */
 int RL_LOCK_GRANTED ; 
 int RL_LOCK_READ ; 
 struct rl_q_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct rl_q_entry*,int /*<<< orphan*/ ) ; 
 struct rl_q_entry* TAILQ_NEXT (struct rl_q_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct rl_q_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ ranges_overlap (struct rl_q_entry*,struct rl_q_entry*) ; 
 int /*<<< orphan*/  rl_q_link ; 
 int /*<<< orphan*/  wakeup (struct rl_q_entry*) ; 

__attribute__((used)) static void
rangelock_calc_block(struct rangelock *lock)
{
	struct rl_q_entry *entry, *nextentry, *entry1;

	for (entry = lock->rl_currdep; entry != NULL; entry = nextentry) {
		nextentry = TAILQ_NEXT(entry, rl_q_link);
		if (entry->rl_q_flags & RL_LOCK_READ) {
			/* Reads must not overlap with granted writes. */
			for (entry1 = TAILQ_FIRST(&lock->rl_waiters);
			    !(entry1->rl_q_flags & RL_LOCK_READ);
			    entry1 = TAILQ_NEXT(entry1, rl_q_link)) {
				if (ranges_overlap(entry, entry1))
					goto out;
			}
		} else {
			/* Write must not overlap with any granted locks. */
			for (entry1 = TAILQ_FIRST(&lock->rl_waiters);
			    entry1 != entry;
			    entry1 = TAILQ_NEXT(entry1, rl_q_link)) {
				if (ranges_overlap(entry, entry1))
					goto out;
			}

			/* Move grantable write locks to the front. */
			TAILQ_REMOVE(&lock->rl_waiters, entry, rl_q_link);
			TAILQ_INSERT_HEAD(&lock->rl_waiters, entry, rl_q_link);
		}

		/* Grant this lock. */
		entry->rl_q_flags |= RL_LOCK_GRANTED;
		wakeup(entry);
	}
out:
	lock->rl_currdep = entry;
}