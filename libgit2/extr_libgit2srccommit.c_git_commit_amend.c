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
typedef  int /*<<< orphan*/  const git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  commit_parent_for_amend ; 
 int git_commit__create_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/ * git_commit_author (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_commit_committer (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/  const*) ; 
 char* git_commit_message (int /*<<< orphan*/  const*) ; 
 char* git_commit_message_encoding (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_commit_owner (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_reference__update_for_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup_resolved (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_tree_owner (int /*<<< orphan*/  const*) ; 

int git_commit_amend(
	git_oid *id,
	const git_commit *commit_to_amend,
	const char *update_ref,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message,
	const git_tree *tree)
{
	git_repository *repo;
	git_oid tree_id;
	git_reference *ref;
	int error;

	assert(id && commit_to_amend);

	repo = git_commit_owner(commit_to_amend);

	if (!author)
		author = git_commit_author(commit_to_amend);
	if (!committer)
		committer = git_commit_committer(commit_to_amend);
	if (!message_encoding)
		message_encoding = git_commit_message_encoding(commit_to_amend);
	if (!message)
		message = git_commit_message(commit_to_amend);

	if (!tree) {
		git_tree *old_tree;
		GIT_ERROR_CHECK_ERROR( git_commit_tree(&old_tree, commit_to_amend) );
		git_oid_cpy(&tree_id, git_tree_id(old_tree));
		git_tree_free(old_tree);
	} else {
		assert(git_tree_owner(tree) == repo);
		git_oid_cpy(&tree_id, git_tree_id(tree));
	}

	if (update_ref) {
		if ((error = git_reference_lookup_resolved(&ref, repo, update_ref, 5)) < 0)
			return error;

		if (git_oid_cmp(git_commit_id(commit_to_amend), git_reference_target(ref))) {
			git_reference_free(ref);
			git_error_set(GIT_ERROR_REFERENCE, "commit to amend is not the tip of the given branch");
			return -1;
		}
	}

	error = git_commit__create_internal(
		id, repo, NULL, author, committer, message_encoding, message,
		&tree_id, commit_parent_for_amend, (void *)commit_to_amend, false);

	if (!error && update_ref) {
		error = git_reference__update_for_commit(
			repo, ref, NULL, id, "commit");
		git_reference_free(ref);
	}

	return error;
}