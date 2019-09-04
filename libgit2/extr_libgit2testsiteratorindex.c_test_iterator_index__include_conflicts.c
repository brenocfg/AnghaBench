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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_ITERATOR_DONT_AUTOEXPAND ; 
 int GIT_ITERATOR_DONT_IGNORE_CASE ; 
 int GIT_ITERATOR_INCLUDE_CONFLICTS ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_NORMAL ; 
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  add_conflict (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_advance_over (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_iterator_index__include_conflicts(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_index *index;

	i_opts.flags |= GIT_ITERATOR_DONT_IGNORE_CASE |
		GIT_ITERATOR_DONT_AUTOEXPAND;

	g_repo = cl_git_sandbox_init("icase");
	cl_git_pass(git_repository_index(&index, g_repo));

	add_conflict(index, "CONFLICT1", "CONFLICT1" ,"CONFLICT1");
	add_conflict(index, "ZZZ-CONFLICT2.ancestor", "ZZZ-CONFLICT2.ours", "ZZZ-CONFLICT2.theirs");
	add_conflict(index, "ancestor.conflict3", "ours.conflict3", "theirs.conflict3");
	add_conflict(index, "zzz-conflict4", "zzz-conflict4", "zzz-conflict4");

	/* Iterate the index, ensuring that conflicts are not included */
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));

	expect_advance_over(i, "B", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "D", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "F", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "H", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "J", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "L/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "a", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "c", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "e", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "g", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "i", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "k/", GIT_ITERATOR_STATUS_NORMAL);

	cl_git_fail_with(GIT_ITEROVER, git_iterator_advance(NULL, i));
	git_iterator_free(i);

	/* Try again, returning conflicts */
	i_opts.flags |= GIT_ITERATOR_INCLUDE_CONFLICTS;

	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));

	expect_advance_over(i, "B", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "CONFLICT1", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "CONFLICT1", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "CONFLICT1", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "D", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "F", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "H", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "J", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "L/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "ZZZ-CONFLICT2.ancestor", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "ZZZ-CONFLICT2.ours", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "ZZZ-CONFLICT2.theirs", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "a", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "ancestor.conflict3", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "c", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "e", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "g", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "i", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "k/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "ours.conflict3", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "theirs.conflict3", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "zzz-conflict4", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "zzz-conflict4", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "zzz-conflict4", GIT_ITERATOR_STATUS_NORMAL);

	cl_git_fail_with(GIT_ITEROVER, git_iterator_advance(NULL, i));
	git_iterator_free(i);

	git_index_free(index);
}