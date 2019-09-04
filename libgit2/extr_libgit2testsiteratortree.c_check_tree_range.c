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
struct TYPE_4__ {char const* start; char const* end; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_ITERATOR_IGNORE_CASE ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_tree_range(
	git_repository *repo,
	const char *start,
	const char *end,
	bool ignore_case,
	int expected_count)
{
	git_tree *head;
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	int error, count;

	i_opts.flags = ignore_case ? GIT_ITERATOR_IGNORE_CASE : GIT_ITERATOR_DONT_IGNORE_CASE;
	i_opts.start = start;
	i_opts.end = end;

	cl_git_pass(git_repository_head_tree(&head, repo));

	cl_git_pass(git_iterator_for_tree(&i, head, &i_opts));

	for (count = 0; !(error = git_iterator_advance(NULL, i)); ++count)
		/* count em up */;

	cl_assert_equal_i(GIT_ITEROVER, error);
	cl_assert_equal_i(expected_count, count);

	git_iterator_free(i);
	git_tree_free(head);
}