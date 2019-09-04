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
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit_list_node ;
typedef  int /*<<< orphan*/  git_commit_list ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_MERGE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_merge__bases_many (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_revwalk__commit_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int merge_bases_many(git_commit_list **out, git_revwalk **walk_out, git_repository *repo, size_t length, const git_oid input_array[])
{
	git_revwalk *walk = NULL;
	git_vector list;
	git_commit_list *result = NULL;
	git_commit_list_node *commit;
	int error = -1;
	unsigned int i;

	if (length < 2) {
		git_error_set(GIT_ERROR_INVALID, "at least two commits are required to find an ancestor");
		return -1;
	}

	if (git_vector_init(&list, length - 1, NULL) < 0)
		return -1;

	if (git_revwalk_new(&walk, repo) < 0)
		goto on_error;

	for (i = 1; i < length; i++) {
		commit = git_revwalk__commit_lookup(walk, &input_array[i]);
		if (commit == NULL)
			goto on_error;

		git_vector_insert(&list, commit);
	}

	commit = git_revwalk__commit_lookup(walk, &input_array[0]);
	if (commit == NULL)
		goto on_error;

	if (git_merge__bases_many(&result, walk, commit, &list) < 0)
		goto on_error;

	if (!result) {
		git_error_set(GIT_ERROR_MERGE, "no merge base found");
		error = GIT_ENOTFOUND;
		goto on_error;
	}

	*out = result;
	*walk_out = walk;

	git_vector_free(&list);
	return 0;

on_error:
	git_vector_free(&list);
	git_revwalk_free(walk);
	return error;
}