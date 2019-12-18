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
typedef  int /*<<< orphan*/  git_tree ;
typedef  scalar_t__ git_reset_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_5__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MSG ; 
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 int GIT_EUNMERGED ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 scalar_t__ GIT_REPOSITORY_STATE_MERGE ; 
 scalar_t__ GIT_RESET_HARD ; 
 scalar_t__ GIT_RESET_MIXED ; 
 scalar_t__ GIT_RESET_SOFT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int git_checkout_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_index_has_conflicts (int /*<<< orphan*/ *) ; 
 int git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_object_owner (int /*<<< orphan*/  const*) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int git_reference__update_terminal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 int git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_state (int /*<<< orphan*/ *) ; 
 int git_repository_state_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reset(
	git_repository *repo,
	const git_object *target,
	const char *to,
	git_reset_t reset_type,
	const git_checkout_options *checkout_opts)
{
	git_object *commit = NULL;
	git_index *index = NULL;
	git_tree *tree = NULL;
	int error = 0;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_buf log_message = GIT_BUF_INIT;

	assert(repo && target);

	if (checkout_opts)
		opts = *checkout_opts;

	if (git_object_owner(target) != repo) {
		git_error_set(GIT_ERROR_OBJECT,
			"%s - The given target does not belong to this repository.", ERROR_MSG);
		return -1;
	}

	if (reset_type != GIT_RESET_SOFT &&
		(error = git_repository__ensure_not_bare(repo,
			reset_type == GIT_RESET_MIXED ? "reset mixed" : "reset hard")) < 0)
		return error;

	if ((error = git_object_peel(&commit, target, GIT_OBJECT_COMMIT)) < 0 ||
		(error = git_repository_index(&index, repo)) < 0 ||
		(error = git_commit_tree(&tree, (git_commit *)commit)) < 0)
		goto cleanup;

	if (reset_type == GIT_RESET_SOFT &&
		(git_repository_state(repo) == GIT_REPOSITORY_STATE_MERGE ||
		 git_index_has_conflicts(index)))
	{
		git_error_set(GIT_ERROR_OBJECT, "%s (soft) in the middle of a merge", ERROR_MSG);
		error = GIT_EUNMERGED;
		goto cleanup;
	}

	if ((error = git_buf_printf(&log_message, "reset: moving to %s", to)) < 0)
		return error;

	if (reset_type == GIT_RESET_HARD) {
		/* overwrite working directory with the new tree */
		opts.checkout_strategy = GIT_CHECKOUT_FORCE;

		if ((error = git_checkout_tree(repo, (git_object *)tree, &opts)) < 0)
			goto cleanup;
	}

	/* move HEAD to the new target */
	if ((error = git_reference__update_terminal(repo, GIT_HEAD_FILE,
		git_object_id(commit), NULL, git_buf_cstr(&log_message))) < 0)
		goto cleanup;

	if (reset_type > GIT_RESET_SOFT) {
		/* reset index to the target content */

		if ((error = git_index_read_tree(index, tree)) < 0 ||
			(error = git_index_write(index)) < 0)
			goto cleanup;

		if ((error = git_repository_state_cleanup(repo)) < 0) {
			git_error_set(GIT_ERROR_INDEX, "%s - failed to clean up merge data", ERROR_MSG);
			goto cleanup;
		}
	}

cleanup:
	git_object_free(commit);
	git_index_free(index);
	git_tree_free(tree);
	git_buf_dispose(&log_message);

	return error;
}