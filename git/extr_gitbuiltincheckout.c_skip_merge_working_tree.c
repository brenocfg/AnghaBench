#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct checkout_opts {scalar_t__ new_orphan_branch; scalar_t__ new_branch_force; int /*<<< orphan*/  new_branch; scalar_t__ ignore_other_worktrees; scalar_t__ ignore_skipworktree; int /*<<< orphan*/  overwrite_ignore; scalar_t__ force_detach; scalar_t__ force; scalar_t__ merge; } ;
struct branch_info {TYPE_2__* commit; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  checkout_optimize_new_branch ; 
 scalar_t__ core_apply_sparse_checkout ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_index_file () ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int skip_merge_working_tree(const struct checkout_opts *opts,
	const struct branch_info *old_branch_info,
	const struct branch_info *new_branch_info)
{
	/*
	 * Do the merge if sparse checkout is on and the user has not opted in
	 * to the optimized behavior
	 */
	if (core_apply_sparse_checkout && !checkout_optimize_new_branch)
		return 0;

	/*
	 * We must do the merge if we are actually moving to a new commit.
	 */
	if (!old_branch_info->commit || !new_branch_info->commit ||
		!oideq(&old_branch_info->commit->object.oid,
		       &new_branch_info->commit->object.oid))
		return 0;

	/*
	 * opts->patch_mode cannot be used with switching branches so is
	 * not tested here
	 */

	/*
	 * opts->quiet only impacts output so doesn't require a merge
	 */

	/*
	 * Honor the explicit request for a three-way merge or to throw away
	 * local changes
	 */
	if (opts->merge || opts->force)
		return 0;

	/*
	 * --detach is documented as "updating the index and the files in the
	 * working tree" but this optimization skips those steps so fall through
	 * to the regular code path.
	 */
	if (opts->force_detach)
		return 0;

	/*
	 * opts->writeout_stage cannot be used with switching branches so is
	 * not tested here
	 */

	/*
	 * Honor the explicit ignore requests
	 */
	if (!opts->overwrite_ignore || opts->ignore_skipworktree ||
		opts->ignore_other_worktrees)
		return 0;

	/*
	 * opts->show_progress only impacts output so doesn't require a merge
	 */

	/*
	 * opts->overlay_mode cannot be used with switching branches so is
	 * not tested here
	 */

	/*
	 * If we aren't creating a new branch any changes or updates will
	 * happen in the existing branch.  Since that could only be updating
	 * the index and working directory, we don't want to skip those steps
	 * or we've defeated any purpose in running the command.
	 */
	if (!opts->new_branch)
		return 0;

	/*
	 * new_branch_force is defined to "create/reset and checkout a branch"
	 * so needs to go through the merge to do the reset
	 */
	if (opts->new_branch_force)
		return 0;

	/*
	 * A new orphaned branch requrires the index and the working tree to be
	 * adjusted to <start_point>
	 */
	if (opts->new_orphan_branch)
		return 0;

	/*
	 * Remaining variables are not checkout options but used to track state
	 */

	 /*
	  * Do the merge if this is the initial checkout. We cannot use
	  * is_cache_unborn() here because the index hasn't been loaded yet
	  * so cache_nr and timestamp.sec are always zero.
	  */
	if (!file_exists(get_index_file()))
		return 0;

	return 1;
}