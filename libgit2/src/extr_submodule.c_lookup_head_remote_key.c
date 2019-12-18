#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int git_branch_remote_name (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_branch_upstream_name (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_is_branch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lookup_head_remote_key(git_buf *remote_name, git_repository *repo)
{
	int error;
	git_reference *head = NULL;
	git_buf upstream_name = GIT_BUF_INIT;

	/* lookup and dereference HEAD */
	if ((error = git_repository_head(&head, repo)) < 0)
		return error;

	/**
	 * If head does not refer to a branch, then return
	 * GIT_ENOTFOUND to indicate that we could not find
	 * a remote key for the local tracking branch HEAD points to.
	 **/
	if (!git_reference_is_branch(head)) {
		git_error_set(GIT_ERROR_INVALID,
			"HEAD does not refer to a branch.");
		error = GIT_ENOTFOUND;
		goto done;
	}

	/* lookup remote tracking branch of HEAD */
	if ((error = git_branch_upstream_name(
		&upstream_name,
		repo,
		git_reference_name(head))) < 0)
		goto done;

	/* lookup remote of remote tracking branch */
	if ((error = git_branch_remote_name(remote_name, repo, upstream_name.ptr)) < 0)
		goto done;

done:
	git_buf_dispose(&upstream_name);
	git_reference_free(head);

	return error;
}