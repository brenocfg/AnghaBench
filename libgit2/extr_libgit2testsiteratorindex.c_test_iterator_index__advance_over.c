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
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_NORMAL ; 
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  create_paths (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  expect_advance_over (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_iterator_index__advance_over(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_index *index;

	i_opts.flags |= GIT_ITERATOR_DONT_IGNORE_CASE |
		GIT_ITERATOR_DONT_AUTOEXPAND;

	g_repo = cl_git_sandbox_init("icase");
	cl_git_pass(git_repository_index(&index, g_repo));

	create_paths(index, NULL, 1);

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
	expect_advance_over(i, "item0", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "item1/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "item2", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "item3/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "item4", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "item5/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "item6", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "item7/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "k/", GIT_ITERATOR_STATUS_NORMAL);

	cl_git_fail_with(GIT_ITEROVER, git_iterator_advance(NULL, i));
	git_iterator_free(i);
	git_index_free(index);
}