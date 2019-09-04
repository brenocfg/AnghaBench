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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int build_untracked_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int commit_untracked(
	git_commit **u_commit,
	git_repository *repo,
	const git_signature *stasher,
	const char *message,
	git_commit *i_commit,
	uint32_t flags)
{
	git_tree *u_tree = NULL;
	git_oid u_commit_oid;
	git_buf msg = GIT_BUF_INIT;
	int error;

	if ((error = build_untracked_tree(&u_tree, repo, i_commit, flags)) < 0)
		goto cleanup;

	if ((error = git_buf_printf(&msg, "untracked files on %s\n", message)) < 0)
		goto cleanup;

	if ((error = git_commit_create(
		&u_commit_oid,
		repo,
		NULL,
		stasher,
		stasher,
		NULL,
		git_buf_cstr(&msg),
		u_tree,
		0,
		NULL)) < 0)
		goto cleanup;

	error = git_commit_lookup(u_commit, repo, &u_commit_oid);

cleanup:
	git_tree_free(u_tree);
	git_buf_dispose(&msg);
	return error;
}