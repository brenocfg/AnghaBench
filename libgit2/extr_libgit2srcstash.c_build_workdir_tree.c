#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stash_update_rules {int include_changed; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_DIFF_IGNORE_SUBMODULES ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int build_tree_from_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_diff__merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stash_delta_merge ; 
 int stash_update_index_from_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct stash_update_rules*) ; 

__attribute__((used)) static int build_workdir_tree(
	git_tree **tree_out,
	git_repository *repo,
	git_index *i_index,
	git_commit *b_commit)
{
	git_tree *b_tree = NULL;
	git_diff *diff = NULL, *idx_to_wd = NULL;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	struct stash_update_rules data = {0};
	int error;

	opts.flags = GIT_DIFF_IGNORE_SUBMODULES | GIT_DIFF_INCLUDE_UNTRACKED;

	if ((error = git_commit_tree(&b_tree, b_commit)) < 0)
		goto cleanup;

	if ((error = git_diff_tree_to_index(&diff, repo, b_tree, i_index, &opts)) < 0 ||
		(error = git_diff_index_to_workdir(&idx_to_wd, repo, i_index, &opts)) < 0 ||
		(error = git_diff__merge(diff, idx_to_wd, stash_delta_merge)) < 0)
		goto cleanup;

	data.include_changed = true;

	if ((error = stash_update_index_from_diff(repo, i_index, diff, &data)) < 0)
		goto cleanup;

	error = build_tree_from_index(tree_out, repo, i_index);

cleanup:
	git_diff_free(idx_to_wd);
	git_diff_free(diff);
	git_tree_free(b_tree);

	return error;
}