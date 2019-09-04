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
struct unpack_trees_options {int /*<<< orphan*/  result; } ;
typedef  struct cache_entry {int ce_flags; int /*<<< orphan*/  oid; } const cache_entry ;

/* Variables and functions */
 int CE_ADDED ; 
 int CE_CONFLICTED ; 
 int CE_NEW_SKIP_WORKTREE ; 
 int CE_SKIP_WORKTREE ; 
 int /*<<< orphan*/  CE_STAGEMASK ; 
 int CE_UPDATE ; 
 int /*<<< orphan*/  ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN ; 
 int check_submodule_move_head (struct cache_entry const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  copy_cache_entry (struct cache_entry const*,struct cache_entry const*) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry const*) ; 
 int /*<<< orphan*/  do_add_entry (struct unpack_trees_options*,struct cache_entry const*,int,int /*<<< orphan*/ ) ; 
 struct cache_entry const* dup_cache_entry (struct cache_entry const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invalidate_ce_path (struct cache_entry const*,struct unpack_trees_options*) ; 
 int /*<<< orphan*/ * oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ same (struct cache_entry const*,struct cache_entry const*) ; 
 scalar_t__ submodule_from_ce (struct cache_entry const*) ; 
 scalar_t__ verify_absent (struct cache_entry const*,int /*<<< orphan*/ ,struct unpack_trees_options*) ; 
 scalar_t__ verify_uptodate (struct cache_entry const*,struct unpack_trees_options*) ; 

__attribute__((used)) static int merged_entry(const struct cache_entry *ce,
			const struct cache_entry *old,
			struct unpack_trees_options *o)
{
	int update = CE_UPDATE;
	struct cache_entry *merge = dup_cache_entry(ce, &o->result);

	if (!old) {
		/*
		 * New index entries. In sparse checkout, the following
		 * verify_absent() will be delayed until after
		 * traverse_trees() finishes in unpack_trees(), then:
		 *
		 *  - CE_NEW_SKIP_WORKTREE will be computed correctly
		 *  - verify_absent() be called again, this time with
		 *    correct CE_NEW_SKIP_WORKTREE
		 *
		 * verify_absent() call here does nothing in sparse
		 * checkout (i.e. o->skip_sparse_checkout == 0)
		 */
		update |= CE_ADDED;
		merge->ce_flags |= CE_NEW_SKIP_WORKTREE;

		if (verify_absent(merge,
				  ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN, o)) {
			discard_cache_entry(merge);
			return -1;
		}
		invalidate_ce_path(merge, o);

		if (submodule_from_ce(ce)) {
			int ret = check_submodule_move_head(ce, NULL,
							    oid_to_hex(&ce->oid),
							    o);
			if (ret)
				return ret;
		}

	} else if (!(old->ce_flags & CE_CONFLICTED)) {
		/*
		 * See if we can re-use the old CE directly?
		 * That way we get the uptodate stat info.
		 *
		 * This also removes the UPDATE flag on a match; otherwise
		 * we will end up overwriting local changes in the work tree.
		 */
		if (same(old, merge)) {
			copy_cache_entry(merge, old);
			update = 0;
		} else {
			if (verify_uptodate(old, o)) {
				discard_cache_entry(merge);
				return -1;
			}
			/* Migrate old flags over */
			update |= old->ce_flags & (CE_SKIP_WORKTREE | CE_NEW_SKIP_WORKTREE);
			invalidate_ce_path(old, o);
		}

		if (submodule_from_ce(ce)) {
			int ret = check_submodule_move_head(ce, oid_to_hex(&old->oid),
							    oid_to_hex(&ce->oid),
							    o);
			if (ret)
				return ret;
		}
	} else {
		/*
		 * Previously unmerged entry left as an existence
		 * marker by read_index_unmerged();
		 */
		invalidate_ce_path(old, o);
	}

	do_add_entry(o, merge, update, CE_STAGEMASK);
	return 1;
}