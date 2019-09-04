#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_iterator_status_t ;
struct TYPE_31__ {scalar_t__ mode; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ git_index_entry ;
struct TYPE_29__ {int /*<<< orphan*/  deltas; } ;
struct TYPE_32__ {TYPE_1__ base; } ;
typedef  TYPE_4__ git_diff_generated ;
struct TYPE_30__ {scalar_t__ mode; } ;
struct TYPE_33__ {TYPE_2__ old_file; scalar_t__ status; } ;
typedef  TYPE_5__ git_diff_delta ;
typedef  scalar_t__ git_delta_t ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_34__ {TYPE_8__* new_iter; TYPE_3__* nitem; int /*<<< orphan*/  repo; int /*<<< orphan*/  oitem; } ;
typedef  TYPE_6__ diff_in_progress ;
struct TYPE_35__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DIFF_FLAG_ISNT_SET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ DIFF_FLAG_IS_SET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOT_GIT ; 
 scalar_t__ GIT_DELTA_ADDED ; 
 scalar_t__ GIT_DELTA_CONFLICTED ; 
 scalar_t__ GIT_DELTA_IGNORED ; 
 scalar_t__ GIT_DELTA_TYPECHANGE ; 
 scalar_t__ GIT_DELTA_UNREADABLE ; 
 scalar_t__ GIT_DELTA_UNTRACKED ; 
 int /*<<< orphan*/  GIT_DIFF_ENABLE_FAST_UNTRACKED_DIRS ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_IGNORED ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_TYPECHANGE_TREES ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNREADABLE_AS_UNTRACKED ; 
 int /*<<< orphan*/  GIT_DIFF_RECURSE_IGNORED_DIRS ; 
 int /*<<< orphan*/  GIT_DIFF_RECURSE_UNTRACKED_DIRS ; 
 int GIT_ENOTFOUND ; 
 scalar_t__ GIT_FILEMODE_COMMIT ; 
 scalar_t__ GIT_FILEMODE_TREE ; 
 scalar_t__ GIT_FILEMODE_UNREADABLE ; 
 scalar_t__ GIT_ITERATOR_STATUS_EMPTY ; 
 scalar_t__ GIT_ITERATOR_STATUS_FILTERED ; 
 scalar_t__ GIT_ITERATOR_STATUS_IGNORED ; 
 scalar_t__ GIT_ITERATOR_TYPE_WORKDIR ; 
 int diff_delta__from_one (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 TYPE_5__* diff_delta__last_for_item (TYPE_4__*,TYPE_3__ const*) ; 
 int entry_is_prefixed (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 int /*<<< orphan*/  git__free (TYPE_5__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_index_entry_is_conflict (TYPE_3__ const*) ; 
 scalar_t__ git_iterator_current_is_ignored (TYPE_8__*) ; 
 scalar_t__ git_iterator_current_tree_is_ignored (TYPE_8__*) ; 
 scalar_t__ git_iterator_current_workdir_path (int /*<<< orphan*/ **,TYPE_8__*) ; 
 scalar_t__ git_path_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_submodule_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_pop (int /*<<< orphan*/ *) ; 
 int iterator_advance (TYPE_3__**,TYPE_8__*) ; 
 int iterator_advance_into (TYPE_3__**,TYPE_8__*) ; 
 int iterator_advance_over (TYPE_3__**,scalar_t__*,TYPE_8__*) ; 

__attribute__((used)) static int handle_unmatched_new_item(
	git_diff_generated *diff, diff_in_progress *info)
{
	int error = 0;
	const git_index_entry *nitem = info->nitem;
	git_delta_t delta_type = GIT_DELTA_UNTRACKED;
	bool contains_oitem;

	/* check if this is a prefix of the other side */
	contains_oitem = entry_is_prefixed(diff, info->oitem, nitem);

	/* update delta_type if this item is conflicted */
	if (git_index_entry_is_conflict(nitem))
		delta_type = GIT_DELTA_CONFLICTED;

	/* update delta_type if this item is ignored */
	else if (git_iterator_current_is_ignored(info->new_iter))
		delta_type = GIT_DELTA_IGNORED;

	if (nitem->mode == GIT_FILEMODE_TREE) {
		bool recurse_into_dir = contains_oitem;

		/* check if user requests recursion into this type of dir */
		recurse_into_dir = contains_oitem ||
			(delta_type == GIT_DELTA_UNTRACKED &&
			 DIFF_FLAG_IS_SET(diff, GIT_DIFF_RECURSE_UNTRACKED_DIRS)) ||
			(delta_type == GIT_DELTA_IGNORED &&
			 DIFF_FLAG_IS_SET(diff, GIT_DIFF_RECURSE_IGNORED_DIRS));

		/* do not advance into directories that contain a .git file */
		if (recurse_into_dir && !contains_oitem) {
			git_buf *full = NULL;
			if (git_iterator_current_workdir_path(&full, info->new_iter) < 0)
				return -1;
			if (full && git_path_contains(full, DOT_GIT)) {
				/* TODO: warning if not a valid git repository */
				recurse_into_dir = false;
			}
		}

		/* still have to look into untracked directories to match core git -
		 * with no untracked files, directory is treated as ignored
		 */
		if (!recurse_into_dir &&
			delta_type == GIT_DELTA_UNTRACKED &&
			DIFF_FLAG_ISNT_SET(diff, GIT_DIFF_ENABLE_FAST_UNTRACKED_DIRS))
		{
			git_diff_delta *last;
			git_iterator_status_t untracked_state;

			/* attempt to insert record for this directory */
			if ((error = diff_delta__from_one(diff, delta_type, NULL, nitem)) != 0)
				return error;

			/* if delta wasn't created (because of rules), just skip ahead */
			last = diff_delta__last_for_item(diff, nitem);
			if (!last)
				return iterator_advance(&info->nitem, info->new_iter);

			/* iterate into dir looking for an actual untracked file */
			if ((error = iterator_advance_over(
					&info->nitem, &untracked_state, info->new_iter)) < 0)
				return error;

			/* if we found nothing that matched our pathlist filter, exclude */
			if (untracked_state == GIT_ITERATOR_STATUS_FILTERED) {
				git_vector_pop(&diff->base.deltas);
				git__free(last);
			}

			/* if we found nothing or just ignored items, update the record */
			if (untracked_state == GIT_ITERATOR_STATUS_IGNORED ||
				untracked_state == GIT_ITERATOR_STATUS_EMPTY) {
				last->status = GIT_DELTA_IGNORED;

				/* remove the record if we don't want ignored records */
				if (DIFF_FLAG_ISNT_SET(diff, GIT_DIFF_INCLUDE_IGNORED)) {
					git_vector_pop(&diff->base.deltas);
					git__free(last);
				}
			}

			return 0;
		}

		/* try to advance into directory if necessary */
		if (recurse_into_dir) {
			error = iterator_advance_into(&info->nitem, info->new_iter);

			/* if directory is empty, can't advance into it, so skip it */
			if (error == GIT_ENOTFOUND) {
				git_error_clear();
				error = iterator_advance(&info->nitem, info->new_iter);
			}

			return error;
		}
	}

	else if (delta_type == GIT_DELTA_IGNORED &&
		DIFF_FLAG_ISNT_SET(diff, GIT_DIFF_RECURSE_IGNORED_DIRS) &&
		git_iterator_current_tree_is_ignored(info->new_iter))
		/* item contained in ignored directory, so skip over it */
		return iterator_advance(&info->nitem, info->new_iter);

	else if (info->new_iter->type != GIT_ITERATOR_TYPE_WORKDIR) {
		if (delta_type != GIT_DELTA_CONFLICTED)
			delta_type = GIT_DELTA_ADDED;
	}

	else if (nitem->mode == GIT_FILEMODE_COMMIT) {
		/* ignore things that are not actual submodules */
		if (git_submodule_lookup(NULL, info->repo, nitem->path) != 0) {
			git_error_clear();
			delta_type = GIT_DELTA_IGNORED;

			/* if this contains a tracked item, treat as normal TREE */
			if (contains_oitem) {
				error = iterator_advance_into(&info->nitem, info->new_iter);
				if (error != GIT_ENOTFOUND)
					return error;

				git_error_clear();
				return iterator_advance(&info->nitem, info->new_iter);
			}
		}
	}

	else if (nitem->mode == GIT_FILEMODE_UNREADABLE) {
		if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_INCLUDE_UNREADABLE_AS_UNTRACKED))
			delta_type = GIT_DELTA_UNTRACKED;
		else
			delta_type = GIT_DELTA_UNREADABLE;
	}

	/* Actually create the record for this item if necessary */
	if ((error = diff_delta__from_one(diff, delta_type, NULL, nitem)) != 0)
		return error;

	/* If user requested TYPECHANGE records, then check for that instead of
	 * just generating an ADDED/UNTRACKED record
	 */
	if (delta_type != GIT_DELTA_IGNORED &&
		DIFF_FLAG_IS_SET(diff, GIT_DIFF_INCLUDE_TYPECHANGE_TREES) &&
		contains_oitem)
	{
		/* this entry was prefixed with a tree - make TYPECHANGE */
		git_diff_delta *last = diff_delta__last_for_item(diff, nitem);
		if (last) {
			last->status = GIT_DELTA_TYPECHANGE;
			last->old_file.mode = GIT_FILEMODE_TREE;
		}
	}

	return iterator_advance(&info->nitem, info->new_iter);
}