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
typedef  int /*<<< orphan*/  git_note_iterator ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

int git_note_commit_iterator_new(
	git_note_iterator **it,
	git_commit *notes_commit)
{
	int error;
	git_tree *tree;

	if ((error = git_commit_tree(&tree, notes_commit)) < 0)
		goto cleanup;

	if ((error = git_iterator_for_tree(it, tree, NULL)) < 0)
		git_iterator_free(*it);

cleanup:
	git_tree_free(tree);

	return error;
}