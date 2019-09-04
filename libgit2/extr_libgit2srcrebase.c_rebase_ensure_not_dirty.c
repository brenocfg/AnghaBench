#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_4__ {int /*<<< orphan*/  ignore_submodules; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_REBASE ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_UNTRACKED ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rebase_ensure_not_dirty(
	git_repository *repo,
	bool check_index,
	bool check_workdir,
	int fail_with)
{
	git_tree *head = NULL;
	git_index *index = NULL;
	git_diff *diff = NULL;
	int error = 0;

	if (check_index) {
		if ((error = git_repository_head_tree(&head, repo)) < 0 ||
			(error = git_repository_index(&index, repo)) < 0 ||
			(error = git_diff_tree_to_index(&diff, repo, head, index, NULL)) < 0)
			goto done;

		if (git_diff_num_deltas(diff) > 0) {
			git_error_set(GIT_ERROR_REBASE, "uncommitted changes exist in index");
			error = fail_with;
			goto done;
		}

		git_diff_free(diff);
		diff = NULL;
	}

	if (check_workdir) {
		git_diff_options diff_opts = GIT_DIFF_OPTIONS_INIT;
		diff_opts.ignore_submodules = GIT_SUBMODULE_IGNORE_UNTRACKED;
		if ((error = git_diff_index_to_workdir(&diff, repo, index, &diff_opts)) < 0)
			goto done;

		if (git_diff_num_deltas(diff) > 0) {
			git_error_set(GIT_ERROR_REBASE, "unstaged changes exist in workdir");
			error = fail_with;
			goto done;
		}
	}

done:
	git_diff_free(diff);
	git_index_free(index);
	git_tree_free(head);

	return error;
}