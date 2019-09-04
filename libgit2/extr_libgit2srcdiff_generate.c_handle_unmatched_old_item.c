#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_diff_generated ;
struct TYPE_12__ {int /*<<< orphan*/  mode; } ;
struct TYPE_13__ {TYPE_1__ new_file; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_delta_t ;
struct TYPE_14__ {int /*<<< orphan*/  old_iter; TYPE_4__* oitem; int /*<<< orphan*/  new_iter; TYPE_4__* nitem; } ;
typedef  TYPE_3__ diff_in_progress ;
struct TYPE_15__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ DIFF_FLAG_ISNT_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DIFF_FLAG_IS_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_DELTA_CONFLICTED ; 
 int /*<<< orphan*/  GIT_DELTA_DELETED ; 
 int /*<<< orphan*/  GIT_DELTA_TYPECHANGE ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_TYPECHANGE_TREES ; 
 int /*<<< orphan*/  GIT_DIFF_RECURSE_UNTRACKED_DIRS ; 
 int /*<<< orphan*/  GIT_FILEMODE_TREE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int diff_delta__from_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* diff_delta__last_for_item (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ entry_is_prefixed (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ git_index_entry_is_conflict (TYPE_4__*) ; 
 int iterator_advance (TYPE_4__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_unmatched_old_item(
	git_diff_generated *diff, diff_in_progress *info)
{
	git_delta_t delta_type = GIT_DELTA_DELETED;
	int error;

	/* update delta_type if this item is conflicted */
	if (git_index_entry_is_conflict(info->oitem))
		delta_type = GIT_DELTA_CONFLICTED;

	if ((error = diff_delta__from_one(diff, delta_type, info->oitem, NULL)) < 0)
		return error;

	/* if we are generating TYPECHANGE records then check for that
	 * instead of just generating a DELETE record
	 */
	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_INCLUDE_TYPECHANGE_TREES) &&
		entry_is_prefixed(diff, info->nitem, info->oitem))
	{
		/* this entry has become a tree! convert to TYPECHANGE */
		git_diff_delta *last = diff_delta__last_for_item(diff, info->oitem);
		if (last) {
			last->status = GIT_DELTA_TYPECHANGE;
			last->new_file.mode = GIT_FILEMODE_TREE;
		}

		/* If new_iter is a workdir iterator, then this situation
		 * will certainly be followed by a series of untracked items.
		 * Unless RECURSE_UNTRACKED_DIRS is set, skip over them...
		 */
		if (S_ISDIR(info->nitem->mode) &&
			DIFF_FLAG_ISNT_SET(diff, GIT_DIFF_RECURSE_UNTRACKED_DIRS))
			return iterator_advance(&info->nitem, info->new_iter);
	}

	return iterator_advance(&info->oitem, info->old_iter);
}