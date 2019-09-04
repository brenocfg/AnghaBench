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
struct unpack_trees_options {int dummy; } ;
struct index_state {int /*<<< orphan*/  cache_changed; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_ENTRY_CHANGED ; 
 int CE_NEW_SKIP_WORKTREE ; 
 int CE_REMOVE ; 
 int CE_SKIP_WORKTREE ; 
 int CE_UPDATE ; 
 int CE_UPDATE_IN_BASE ; 
 int CE_WT_REMOVE ; 
 int /*<<< orphan*/  ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN ; 
 int ce_skip_worktree (struct cache_entry*) ; 
 int /*<<< orphan*/  mark_fsmonitor_invalid (struct index_state*,struct cache_entry*) ; 
 scalar_t__ verify_absent_sparse (struct cache_entry*,int /*<<< orphan*/ ,struct unpack_trees_options*) ; 
 scalar_t__ verify_uptodate_sparse (struct cache_entry*,struct unpack_trees_options*) ; 

__attribute__((used)) static int apply_sparse_checkout(struct index_state *istate,
				 struct cache_entry *ce,
				 struct unpack_trees_options *o)
{
	int was_skip_worktree = ce_skip_worktree(ce);

	if (ce->ce_flags & CE_NEW_SKIP_WORKTREE)
		ce->ce_flags |= CE_SKIP_WORKTREE;
	else
		ce->ce_flags &= ~CE_SKIP_WORKTREE;
	if (was_skip_worktree != ce_skip_worktree(ce)) {
		ce->ce_flags |= CE_UPDATE_IN_BASE;
		mark_fsmonitor_invalid(istate, ce);
		istate->cache_changed |= CE_ENTRY_CHANGED;
	}

	/*
	 * if (!was_skip_worktree && !ce_skip_worktree()) {
	 *	This is perfectly normal. Move on;
	 * }
	 */

	/*
	 * Merge strategies may set CE_UPDATE|CE_REMOVE outside checkout
	 * area as a result of ce_skip_worktree() shortcuts in
	 * verify_absent() and verify_uptodate().
	 * Make sure they don't modify worktree if they are already
	 * outside checkout area
	 */
	if (was_skip_worktree && ce_skip_worktree(ce)) {
		ce->ce_flags &= ~CE_UPDATE;

		/*
		 * By default, when CE_REMOVE is on, CE_WT_REMOVE is also
		 * on to get that file removed from both index and worktree.
		 * If that file is already outside worktree area, don't
		 * bother remove it.
		 */
		if (ce->ce_flags & CE_REMOVE)
			ce->ce_flags &= ~CE_WT_REMOVE;
	}

	if (!was_skip_worktree && ce_skip_worktree(ce)) {
		/*
		 * If CE_UPDATE is set, verify_uptodate() must be called already
		 * also stat info may have lost after merged_entry() so calling
		 * verify_uptodate() again may fail
		 */
		if (!(ce->ce_flags & CE_UPDATE) && verify_uptodate_sparse(ce, o))
			return -1;
		ce->ce_flags |= CE_WT_REMOVE;
		ce->ce_flags &= ~CE_UPDATE;
	}
	if (was_skip_worktree && !ce_skip_worktree(ce)) {
		if (verify_absent_sparse(ce, ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN, o))
			return -1;
		ce->ce_flags |= CE_UPDATE;
	}
	return 0;
}