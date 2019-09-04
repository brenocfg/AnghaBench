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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ git_branch_is_checked_out (int /*<<< orphan*/ *) ; 
 int git_branch_is_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_join (int /*<<< orphan*/ *,char,char*,scalar_t__) ; 
 scalar_t__ git_config_rename_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int git_reference_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_is_branch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_is_remote (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_owner (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int git_branch_delete(git_reference *branch)
{
	int is_head;
	git_buf config_section = GIT_BUF_INIT;
	int error = -1;

	assert(branch);

	if (!git_reference_is_branch(branch) && !git_reference_is_remote(branch)) {
		git_error_set(GIT_ERROR_INVALID, "reference '%s' is not a valid branch.",
			git_reference_name(branch));
		return GIT_ENOTFOUND;
	}

	if ((is_head = git_branch_is_head(branch)) < 0)
		return is_head;

	if (is_head) {
		git_error_set(GIT_ERROR_REFERENCE, "cannot delete branch '%s' as it is "
			"the current HEAD of the repository.", git_reference_name(branch));
		return -1;
	}

	if (git_reference_is_branch(branch) && git_branch_is_checked_out(branch)) {
		git_error_set(GIT_ERROR_REFERENCE, "Cannot delete branch '%s' as it is "
			"the current HEAD of a linked repository.", git_reference_name(branch));
		return -1;
	}

	if (git_buf_join(&config_section, '.', "branch",
			git_reference_name(branch) + strlen(GIT_REFS_HEADS_DIR)) < 0)
		goto on_error;

	if (git_config_rename_section(
		git_reference_owner(branch), git_buf_cstr(&config_section), NULL) < 0)
		goto on_error;

	error = git_reference_delete(branch);

on_error:
	git_buf_dispose(&config_section);
	return error;
}