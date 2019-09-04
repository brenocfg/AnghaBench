#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_rebase_operation ;
struct TYPE_6__ {int /*<<< orphan*/  repo; int /*<<< orphan*/  current; int /*<<< orphan*/  operations; } ;
typedef  TYPE_2__ git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_EAPPLIED ; 
 int /*<<< orphan*/  GIT_ERROR_REBASE ; 
 int GIT_EUNMERGED ; 
 TYPE_1__* git_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_commit_author (int /*<<< orphan*/ *) ; 
 int git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* git_commit_message (int /*<<< orphan*/ *) ; 
 char* git_commit_message_encoding (int /*<<< orphan*/ *) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_index_has_conflicts (int /*<<< orphan*/ *) ; 
 int git_index_write_tree_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_id (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rebase_commit__create(
	git_commit **out,
	git_rebase *rebase,
	git_index *index,
	git_commit *parent_commit,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message)
{
	git_rebase_operation *operation;
	git_commit *current_commit = NULL, *commit = NULL;
	git_tree *parent_tree = NULL, *tree = NULL;
	git_oid tree_id, commit_id;
	int error;

	operation = git_array_get(rebase->operations, rebase->current);

	if (git_index_has_conflicts(index)) {
		git_error_set(GIT_ERROR_REBASE, "conflicts have not been resolved");
		error = GIT_EUNMERGED;
		goto done;
	}

	if ((error = git_commit_lookup(&current_commit, rebase->repo, &operation->id)) < 0 ||
		(error = git_commit_tree(&parent_tree, parent_commit)) < 0 ||
		(error = git_index_write_tree_to(&tree_id, index, rebase->repo)) < 0 ||
		(error = git_tree_lookup(&tree, rebase->repo, &tree_id)) < 0)
		goto done;

	if (git_oid_equal(&tree_id, git_tree_id(parent_tree))) {
		git_error_set(GIT_ERROR_REBASE, "this patch has already been applied");
		error = GIT_EAPPLIED;
		goto done;
	}

	if (!author)
		author = git_commit_author(current_commit);

	if (!message) {
		message_encoding = git_commit_message_encoding(current_commit);
		message = git_commit_message(current_commit);
	}

	if ((error = git_commit_create(&commit_id, rebase->repo, NULL, author,
		committer, message_encoding, message, tree, 1,
		(const git_commit **)&parent_commit)) < 0 ||
		(error = git_commit_lookup(&commit, rebase->repo, &commit_id)) < 0)
		goto done;

	*out = commit;

done:
	if (error < 0)
		git_commit_free(commit);

	git_commit_free(current_commit);
	git_tree_free(parent_tree);
	git_tree_free(tree);

	return error;
}