#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_15__ {scalar_t__ count; } ;
typedef  TYPE_3__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_16__ {char* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_4__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_17__ {int /*<<< orphan*/  flags; TYPE_3__ pathspec; } ;
typedef  TYPE_5__ git_diff_options ;
struct TYPE_14__ {scalar_t__ path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
struct TYPE_13__ {int /*<<< orphan*/  path; } ;
struct TYPE_18__ {scalar_t__ status; TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_6__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MSG ; 
 scalar_t__ GIT_DELTA_ADDED ; 
 scalar_t__ GIT_DELTA_CONFLICTED ; 
 scalar_t__ GIT_DELTA_DELETED ; 
 scalar_t__ GIT_DELTA_MODIFIED ; 
 TYPE_5__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_REVERSE ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_6__* git_diff_get_delta (int /*<<< orphan*/ *,size_t) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int git_index_add (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int git_index_conflict_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_index_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_object_owner (int /*<<< orphan*/  const*) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

int git_reset_default(
	git_repository *repo,
	const git_object *target,
	const git_strarray* pathspecs)
{
	git_object *commit = NULL;
	git_tree *tree = NULL;
	git_diff *diff = NULL;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	size_t i, max_i;
	git_index_entry entry;
	int error;
	git_index *index = NULL;

	assert(pathspecs != NULL && pathspecs->count > 0);

	memset(&entry, 0, sizeof(git_index_entry));

	if ((error = git_repository_index(&index, repo)) < 0)
		goto cleanup;

	if (target) {
		if (git_object_owner(target) != repo) {
			git_error_set(GIT_ERROR_OBJECT,
				"%s_default - The given target does not belong to this repository.", ERROR_MSG);
			return -1;
		}

		if ((error = git_object_peel(&commit, target, GIT_OBJECT_COMMIT)) < 0 ||
			(error = git_commit_tree(&tree, (git_commit *)commit)) < 0)
			goto cleanup;
	}

	opts.pathspec = *pathspecs;
	opts.flags = GIT_DIFF_REVERSE;

	if ((error = git_diff_tree_to_index(
		&diff, repo, tree, index, &opts)) < 0)
			goto cleanup;

	for (i = 0, max_i = git_diff_num_deltas(diff); i < max_i; ++i) {
		const git_diff_delta *delta = git_diff_get_delta(diff, i);

		assert(delta->status == GIT_DELTA_ADDED ||
			delta->status == GIT_DELTA_MODIFIED ||
			delta->status == GIT_DELTA_CONFLICTED ||
			delta->status == GIT_DELTA_DELETED);

		error = git_index_conflict_remove(index, delta->old_file.path);
		if (error < 0) {
			if (delta->status == GIT_DELTA_ADDED && error == GIT_ENOTFOUND)
				git_error_clear();
			else
				goto cleanup;
		}

		if (delta->status == GIT_DELTA_DELETED) {
			if ((error = git_index_remove(index, delta->old_file.path, 0)) < 0)
				goto cleanup;
		} else {
			entry.mode = delta->new_file.mode;
			git_oid_cpy(&entry.id, &delta->new_file.id);
			entry.path = (char *)delta->new_file.path;

			if ((error = git_index_add(index, &entry)) < 0)
				goto cleanup;
		}
	}

	error = git_index_write(index);

cleanup:
	git_object_free(commit);
	git_tree_free(tree);
	git_index_free(index);
	git_diff_free(diff);

	return error;
}