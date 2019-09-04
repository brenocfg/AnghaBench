#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * strings; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ git_strarray ;
struct TYPE_6__ {int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_4__ fixture ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_worktree_list (TYPE_1__*,int /*<<< orphan*/ ) ; 

void test_worktree_worktree__list_in_worktree_repo(void)
{
	git_strarray wts;

	cl_git_pass(git_worktree_list(&wts, fixture.worktree));
	cl_assert_equal_i(wts.count, 1);
	cl_assert_equal_s(wts.strings[0], "testrepo-worktree");

	git_strarray_free(&wts);
}