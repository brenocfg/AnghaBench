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
typedef  int /*<<< orphan*/  git_submodule_ignore_t ;
typedef  int /*<<< orphan*/  git_submodule ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_ignore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_set_ignore (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void assert_ignore_change(git_submodule_ignore_t ignore)
{
	git_submodule *sm;

	cl_git_pass(git_submodule_set_ignore(g_repo, "sm_changed_head", ignore));

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_changed_head"));
	cl_assert_equal_i(ignore, git_submodule_ignore(sm));
	git_submodule_free(sm);
}