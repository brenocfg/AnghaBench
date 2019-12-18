#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_8__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIGMAP_IGNORECASE ; 
 int build_workdir_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 scalar_t__ git_index__fill (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index__set_ignore_case (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int git_index_new (TYPE_1__**) ; 
 int git_repository__configmap_lookup (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_index (TYPE_1__**,int /*<<< orphan*/ *) ; 
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
	const git_commit *parents[] = {	NULL, NULL, NULL };
	git_index *i_index = NULL, *r_index = NULL;
	git_tree *w_tree = NULL;
	int error = 0, ignorecase;

	parents[0] = b_commit;
	parents[1] = i_commit;
	parents[2] = u_commit;

	if ((error = git_repository_index(&r_index, repo) < 0) ||
	    (error = git_index_new(&i_index)) < 0 ||
	    (error = git_index__fill(i_index, &r_index->entries) < 0) ||
	    (error = git_repository__configmap_lookup(&ignorecase, repo, GIT_CONFIGMAP_IGNORECASE)) < 0)
		goto cleanup;

	git_index__set_ignore_case(i_index, ignorecase);

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
	git_tree_free(w_tree);
	git_index_free(i_index);
	git_index_free(r_index);
	return error;
}