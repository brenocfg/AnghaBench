#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  locked; int /*<<< orphan*/  commondir_path; int /*<<< orphan*/  parent_path; int /*<<< orphan*/  gitlink_path; int /*<<< orphan*/  gitdir_path; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_worktree ;
struct TYPE_7__ {int /*<<< orphan*/  repo; int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORKTREE_REPO ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_5__ fixture ; 
 int /*<<< orphan*/  git_worktree_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_worktree_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_worktree_open_from_repository (TYPE_1__**,int /*<<< orphan*/ ) ; 

void test_worktree_open__open_from_repository(void)
{
	git_worktree *opened, *lookedup;

	cl_git_pass(git_worktree_open_from_repository(&opened, fixture.worktree));
	cl_git_pass(git_worktree_lookup(&lookedup, fixture.repo, WORKTREE_REPO));

	cl_assert_equal_s(opened->name, lookedup->name);
	cl_assert_equal_s(opened->gitdir_path, lookedup->gitdir_path);
	cl_assert_equal_s(opened->gitlink_path, lookedup->gitlink_path);
	cl_assert_equal_s(opened->parent_path, lookedup->parent_path);
	cl_assert_equal_s(opened->commondir_path, lookedup->commondir_path);
	cl_assert_equal_i(opened->locked, lookedup->locked);

	git_worktree_free(opened);
	git_worktree_free(lookedup);
}