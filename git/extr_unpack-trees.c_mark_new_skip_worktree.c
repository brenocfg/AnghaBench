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
struct pattern_list {int dummy; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_CONFLICTED ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry*) ; 
 int /*<<< orphan*/  clear_ce_flags (struct index_state*,int,int,struct pattern_list*) ; 

__attribute__((used)) static void mark_new_skip_worktree(struct pattern_list *pl,
				   struct index_state *istate,
				   int select_flag, int skip_wt_flag)
{
	int i;

	/*
	 * 1. Pretend the narrowest worktree: only unmerged entries
	 * are checked out
	 */
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];

		if (select_flag && !(ce->ce_flags & select_flag))
			continue;

		if (!ce_stage(ce) && !(ce->ce_flags & CE_CONFLICTED))
			ce->ce_flags |= skip_wt_flag;
		else
			ce->ce_flags &= ~skip_wt_flag;
	}

	/*
	 * 2. Widen worktree according to sparse-checkout file.
	 * Matched entries will have skip_wt_flag cleared (i.e. "in")
	 */
	clear_ce_flags(istate, select_flag, skip_wt_flag, pl);
}