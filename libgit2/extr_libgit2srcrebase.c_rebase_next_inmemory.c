#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_rebase_operation ;
struct TYPE_7__ {int /*<<< orphan*/  merge_options; } ;
struct TYPE_9__ {int /*<<< orphan*/ * index; TYPE_1__ options; int /*<<< orphan*/  repo; int /*<<< orphan*/ * last_commit; int /*<<< orphan*/  current; int /*<<< orphan*/  operations; } ;
typedef  TYPE_3__ git_rebase ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REBASE ; 
 TYPE_2__* git_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_commit_parent (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int git_commit_parentcount (int /*<<< orphan*/ *) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_index_read_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_merge_trees (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rebase_next_inmemory(
	git_rebase_operation **out,
	git_rebase *rebase)
{
	git_commit *current_commit = NULL, *parent_commit = NULL;
	git_tree *current_tree = NULL, *head_tree = NULL, *parent_tree = NULL;
	git_rebase_operation *operation;
	git_index *index = NULL;
	unsigned int parent_count;
	int error;

	*out = NULL;

	operation = git_array_get(rebase->operations, rebase->current);

	if ((error = git_commit_lookup(&current_commit, rebase->repo, &operation->id)) < 0 ||
		(error = git_commit_tree(&current_tree, current_commit)) < 0)
		goto done;

	if ((parent_count = git_commit_parentcount(current_commit)) > 1) {
		git_error_set(GIT_ERROR_REBASE, "cannot rebase a merge commit");
		error = -1;
		goto done;
	} else if (parent_count) {
		if ((error = git_commit_parent(&parent_commit, current_commit, 0)) < 0 ||
			(error = git_commit_tree(&parent_tree, parent_commit)) < 0)
			goto done;
	}

	if ((error = git_commit_tree(&head_tree, rebase->last_commit)) < 0 ||
		(error = git_merge_trees(&index, rebase->repo, parent_tree, head_tree, current_tree, &rebase->options.merge_options)) < 0)
		goto done;

	if (!rebase->index) {
		rebase->index = index;
		index = NULL;
	} else {
		if ((error = git_index_read_index(rebase->index, index)) < 0)
			goto done;
	}

	*out = operation;

done:
	git_commit_free(current_commit);
	git_commit_free(parent_commit);
	git_tree_free(current_tree);
	git_tree_free(head_tree);
	git_tree_free(parent_tree);
	git_index_free(index);

	return error;
}