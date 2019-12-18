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
struct TYPE_4__ {int /*<<< orphan*/  count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _remote_name ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_rename (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_network_remote_rename__renaming_a_remote_moves_the_underlying_reference(void)
{
	git_reference *underlying;
	git_strarray problems = {0};

	cl_assert_equal_i(GIT_ENOTFOUND, git_reference_lookup(&underlying, _repo, "refs/remotes/just/renamed"));
	cl_git_pass(git_reference_lookup(&underlying, _repo, "refs/remotes/test/master"));
	git_reference_free(underlying);

	cl_git_pass(git_remote_rename(&problems, _repo, _remote_name, "just/renamed"));
	cl_assert_equal_i(0, problems.count);
	git_strarray_free(&problems);

	cl_assert_equal_i(GIT_ENOTFOUND, git_reference_lookup(&underlying, _repo, "refs/remotes/test/master"));
	cl_git_pass(git_reference_lookup(&underlying, _repo, "refs/remotes/just/renamed/master"));
	git_reference_free(underlying);
}