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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  GIT_RESET_SOFT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 
 int reuc_entry_exists () ; 
 int /*<<< orphan*/  test_index_reuc__add () ; 

void test_index_reuc__retained_on_reset_soft(void)
{
	git_object *target;

	cl_git_pass(git_revparse_single(&target, repo, "3a34580"));

	cl_git_pass(git_reset(repo, target, GIT_RESET_HARD, NULL));

	test_index_reuc__add();
	cl_git_pass(git_reset(repo, target, GIT_RESET_SOFT, NULL));
	cl_assert(reuc_entry_exists() == true);

	git_object_free(target);
}