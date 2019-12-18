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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  const git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/  const*) ; 
 int git_commit_parent (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 size_t git_commit_parentcount (int /*<<< orphan*/  const*) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

int git_diff__commit(
	git_diff **out,
	git_repository *repo,
	const git_commit *commit,
	const git_diff_options *opts)
{
	git_commit *parent = NULL;
	git_diff *commit_diff = NULL;
	git_tree *old_tree = NULL, *new_tree = NULL;
	size_t parents;
	int error = 0;

	*out = NULL;

	if ((parents = git_commit_parentcount(commit)) > 1) {
		char commit_oidstr[GIT_OID_HEXSZ + 1];

		error = -1;
		git_error_set(GIT_ERROR_INVALID, "commit %s is a merge commit",
			git_oid_tostr(commit_oidstr, GIT_OID_HEXSZ + 1, git_commit_id(commit)));
		goto on_error;
	}

	if (parents > 0)
		if ((error = git_commit_parent(&parent, commit, 0)) < 0 ||
			(error = git_commit_tree(&old_tree, parent)) < 0)
				goto on_error;

	if ((error = git_commit_tree(&new_tree, commit)) < 0 ||
		(error = git_diff_tree_to_tree(&commit_diff, repo, old_tree, new_tree, opts)) < 0)
			goto on_error;

	*out = commit_diff;

on_error:
	git_tree_free(new_tree);
	git_tree_free(old_tree);
	git_commit_free(parent);

	return error;
}