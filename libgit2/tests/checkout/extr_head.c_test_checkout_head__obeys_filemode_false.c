#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_3__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  p_chmod (char*,int) ; 

void test_checkout_head__obeys_filemode_false(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_object *target, *branch;

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	/* In this commit, `README` is executable */
	cl_git_pass(git_revparse_single(&target, g_repo, "f9ed4af42472941da45a3c"));
	cl_git_pass(git_reset(g_repo, target, GIT_RESET_HARD, NULL));

	cl_repo_set_bool(g_repo, "core.filemode", false);
	cl_must_pass(p_chmod("testrepo/README", 0644));

	/*
	 * Checkout will fail with a conflict; the file contents are updated
	 * in the checkout target, but the filemode has changed in our branch.
	 */
	cl_git_pass(git_revparse_single(&branch, g_repo, "099fabac3a9ea935598528c27f866e34089c2eff"));

	opts.checkout_strategy &= ~GIT_CHECKOUT_FORCE;
	opts.checkout_strategy |=  GIT_CHECKOUT_SAFE;
	cl_git_pass(git_checkout_tree(g_repo, branch, NULL));

	git_object_free(branch);
	git_object_free(target);
}