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
struct rl_q_entry {int rl_q_flags; scalar_t__ rl_q_start; scalar_t__ rl_q_end; } ;
struct rangelock {int dummy; } ;
struct mtx {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int RL_LOCK_GRANTED ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  rangelock_calc_block (struct rangelock*) ; 
 int /*<<< orphan*/  rangelock_unlock_locked (struct rangelock*,void*,struct mtx*,int) ; 

void *
rangelock_unlock_range(struct rangelock *lock, void *cookie, off_t start,
    off_t end, struct mtx *ilk)
{
	struct rl_q_entry *entry;

	MPASS(lock != NULL && cookie != NULL && ilk != NULL);
	entry = cookie;
	KASSERT(entry->rl_q_flags & RL_LOCK_GRANTED,
	    ("Unlocking non-granted lock"));
	KASSERT(entry->rl_q_start == start, ("wrong start"));
	KASSERT(entry->rl_q_end >= end, ("wrong end"));

	mtx_lock(ilk);
	if (entry->rl_q_end == end) {
		rangelock_unlock_locked(lock, cookie, ilk, true);
		return (NULL);
	}
	entry->rl_q_end = end;
	rangelock_calc_block(lock);
	mtx_unlock(ilk);
	return (cookie);
}