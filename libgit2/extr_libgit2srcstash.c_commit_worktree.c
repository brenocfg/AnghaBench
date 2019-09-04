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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CVAR_IGNORECASE ; 
 int build_workdir_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index__set_ignore_case (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_index_new (int /*<<< orphan*/ **) ; 
 int git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository__cvar (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int commit_worktree(
	git_oid *w_commit_oid,
	git_repository *repo,
	const git_signature *stasher,
	const char *message,
	git_commit *i_commit,
	git_commit *b_commit,
	git_commit *u_commit)
{
	int error = 0;
	git_tree *w_tree = NULL, *i_tree = NULL;
	git_index *i_index = NULL;
	const git_commit *parents[] = {	NULL, NULL,	NULL };
	int ignorecase;

	parents[0] = b_commit;
	parents[1] = i_commit;
	parents[2] = u_commit;

	if ((error = git_commit_tree(&i_tree, i_commit)) < 0)
		goto cleanup;

	if ((error = git_index_new(&i_index)) < 0 ||
		(error = git_repository__cvar(&ignorecase, repo, GIT_CVAR_IGNORECASE)) < 0)
		goto cleanup;

	git_index__set_ignore_case(i_index, ignorecase);

	if ((error = git_index_read_tree(i_index, i_tree)) < 0)
		goto cleanup;

	if ((error = build_workdir_tree(&w_tree, repo, i_index, b_commit)) < 0)
		goto cleanup;

	error = git_commit_create(
		w_commit_oid,
		repo,
		NULL,
		stasher,
		stasher,
		NULL,
		message,
		w_tree,
		u_commit ? 3 : 2,
		parents);

cleanup:
	git_tree_free(i_tree);
	git_tree_free(w_tree);
	git_index_free(i_index);
	return error;
}