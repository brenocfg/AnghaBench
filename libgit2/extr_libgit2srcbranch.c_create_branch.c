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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__strcmp (char const*,char*) ; 
 int git_branch_is_head (int /*<<< orphan*/ *) ; 
 scalar_t__ git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * git_object_owner (int /*<<< orphan*/  const*) ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_repository_is_bare (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_branch(
	git_reference **ref_out,
	git_repository *repository,
	const char *branch_name,
	const git_commit *commit,
	const char *from,
	int force)
{
	int is_unmovable_head = 0;
	git_reference *branch = NULL;
	git_buf canonical_branch_name = GIT_BUF_INIT,
			  log_message = GIT_BUF_INIT;
	int error = -1;
	int bare = git_repository_is_bare(repository);

	assert(branch_name && commit && ref_out);
	assert(git_object_owner((const git_object *)commit) == repository);

	if (!git__strcmp(branch_name, "HEAD")) {
		git_error_set(GIT_ERROR_REFERENCE, "'HEAD' is not a valid branch name");
		error = -1;
		goto cleanup;
	}

	if (force && !bare && git_branch_lookup(&branch, repository, branch_name, GIT_BRANCH_LOCAL) == 0) {
		error = git_branch_is_head(branch);
		git_reference_free(branch);
		branch = NULL;

		if (error < 0)
			goto cleanup;

		is_unmovable_head = error;
	}

	if (is_unmovable_head && force) {
		git_error_set(GIT_ERROR_REFERENCE, "cannot force update branch '%s' as it is "
			"the current HEAD of the repository.", branch_name);
		error = -1;
		goto cleanup;
	}

	if (git_buf_joinpath(&canonical_branch_name, GIT_REFS_HEADS_DIR, branch_name) < 0)
		goto cleanup;

	if (git_buf_printf(&log_message, "branch: Created from %s", from) < 0)
		goto cleanup;

	error = git_reference_create(&branch, repository,
		git_buf_cstr(&canonical_branch_name), git_commit_id(commit), force,
		git_buf_cstr(&log_message));

	if (!error)
		*ref_out = branch;

cleanup:
	git_buf_dispose(&canonical_branch_name);
	git_buf_dispose(&log_message);
	return error;
}