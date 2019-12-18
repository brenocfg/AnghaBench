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
struct rl_q_entry {int dummy; } ;
struct rangelock {int /*<<< orphan*/  rl_waiters; struct rl_q_entry* rl_currdep; } ;
struct mtx {int dummy; } ;
struct TYPE_2__ {struct rl_q_entry* td_rlqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/ * TAILQ_NEXT (struct rl_q_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct rl_q_entry*,int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  mtx_assert (struct mtx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  rangelock_calc_block (struct rangelock*) ; 
 int /*<<< orphan*/  rl_q_link ; 
 int /*<<< orphan*/  rlqentry_free (struct rl_q_entry*) ; 

__attribute__((used)) static void
rangelock_unlock_locked(struct rangelock *lock, struct rl_q_entry *entry,
    struct mtx *ilk, bool do_calc_block)
{

	MPASS(lock != NULL && entry != NULL && ilk != NULL);
	mtx_assert(ilk, MA_OWNED);

	if (!do_calc_block) {
		/*
		 * This is the case where rangelock_enqueue() has been called
		 * with trylock == true and just inserted this entry in the
		 * queue.
		 * If rl_currdep is this entry, rl_currdep needs to
		 * be set to the next entry in the rl_waiters list.
		 * However, since this entry is the last entry in the
		 * list, the next entry is NULL.
		 */
		if (lock->rl_currdep == entry) {
			KASSERT(TAILQ_NEXT(lock->rl_currdep, rl_q_link) == NULL,
			    ("rangelock_enqueue: next entry not NULL"));
			lock->rl_currdep = NULL;
		}
	} else
		KASSERT(entry != lock->rl_currdep, ("stuck currdep"));

	TAILQ_REMOVE(&lock->rl_waiters, entry, rl_q_link);
	if (do_calc_block)
		rangelock_calc_block(lock);
	mtx_unlock(ilk);
	if (curthread->td_rlqe == NULL)
		curthread->td_rlqe = entry;
	else
		rlqentry_free(entry);
}