#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_INCLUDE_HASH ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_walk (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterator_eq ; 

void validate_workdir_unchanged(git_repository *repo)
{
	git_tree *head;
	git_index *index;
	git_iterator *head_iterator, *workdir_iterator, *iterators[2];
	git_iterator_options workdir_opts = GIT_ITERATOR_OPTIONS_INIT;

	cl_git_pass(git_repository_head_tree(&head, repo));
	cl_git_pass(git_repository_index(&index, repo));

	workdir_opts.flags |= GIT_ITERATOR_INCLUDE_HASH;

	cl_git_pass(git_iterator_for_tree(&head_iterator, head, NULL));
	cl_git_pass(git_iterator_for_workdir(&workdir_iterator, repo, index, NULL, &workdir_opts));

	iterators[0] = head_iterator;
	iterators[1] = workdir_iterator;

	cl_git_pass(git_iterator_walk(iterators, 2, iterator_eq, NULL));

	git_iterator_free(head_iterator);
	git_iterator_free(workdir_iterator);

	git_tree_free(head);
	git_index_free(index);
}