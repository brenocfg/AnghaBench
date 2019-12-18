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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_STASH_INCLUDE_IGNORED ; 
 int GIT_STASH_INCLUDE_UNTRACKED ; 
 int GIT_STASH_KEEP_INDEX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int commit_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int commit_untracked (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int commit_worktree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ensure_there_are_changes_to_stash (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_rtrim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 int git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int prepare_worktree_commit_message (int /*<<< orphan*/ *,char const*) ; 
 int reset_index_and_workdir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int retrieve_base_commit_and_message (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int update_reflog (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_stash_save(
	git_oid *out,
	git_repository *repo,
	const git_signature *stasher,
	const char *message,
	uint32_t flags)
{
	git_index *index = NULL;
	git_commit *b_commit = NULL, *i_commit = NULL, *u_commit = NULL;
	git_buf msg = GIT_BUF_INIT;
	int error;

	assert(out && repo && stasher);

	if ((error = git_repository__ensure_not_bare(repo, "stash save")) < 0)
		return error;

	if ((error = retrieve_base_commit_and_message(&b_commit, &msg, repo)) < 0)
		goto cleanup;

	if ((error = ensure_there_are_changes_to_stash(repo, flags)) < 0)
		goto cleanup;

	if ((error = git_repository_index(&index, repo)) < 0)
		goto cleanup;

	if ((error = commit_index(&i_commit, repo, index, stasher,
				  git_buf_cstr(&msg), b_commit)) < 0)
		goto cleanup;

	if ((flags & (GIT_STASH_INCLUDE_UNTRACKED | GIT_STASH_INCLUDE_IGNORED)) &&
	    (error = commit_untracked(&u_commit, repo, stasher,
				      git_buf_cstr(&msg), i_commit, flags)) < 0)
		goto cleanup;

	if ((error = prepare_worktree_commit_message(&msg, message)) < 0)
		goto cleanup;

	if ((error = commit_worktree(out, repo, stasher, git_buf_cstr(&msg),
				     i_commit, b_commit, u_commit)) < 0)
		goto cleanup;

	git_buf_rtrim(&msg);

	if ((error = update_reflog(out, repo, git_buf_cstr(&msg))) < 0)
		goto cleanup;

	if ((error = reset_index_and_workdir(repo, (flags & GIT_STASH_KEEP_INDEX) ? i_commit : b_commit,
					     flags)) < 0)
		goto cleanup;

cleanup:

	git_buf_dispose(&msg);
	git_commit_free(i_commit);
	git_commit_free(b_commit);
	git_commit_free(u_commit);
	git_index_free(index);

	return error;
}