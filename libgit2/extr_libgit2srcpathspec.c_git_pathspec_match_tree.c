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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_pathspec_match_list ;
typedef  int /*<<< orphan*/  git_pathspec ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int pathspec_match_from_iterator (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pathspec_match_iter_flags (int /*<<< orphan*/ ) ; 

int git_pathspec_match_tree(
	git_pathspec_match_list **out,
	git_tree *tree,
	uint32_t flags,
	git_pathspec *ps)
{
	git_iterator *iter;
	git_iterator_options iter_opts = GIT_ITERATOR_OPTIONS_INIT;
	int error = 0;

	assert(tree);

	iter_opts.flags = pathspec_match_iter_flags(flags);

	if (!(error = git_iterator_for_tree(&iter, tree, &iter_opts))) {
		error = pathspec_match_from_iterator(out, iter, flags, ps);
		git_iterator_free(iter);
	}

	return error;
}