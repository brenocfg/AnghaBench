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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_rename (char*,char*) ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup_resolved (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_checkout_icase__ignores_unstaged_casechange(void)
{
	git_reference *orig_ref, *br2_ref;
	git_commit *orig, *br2;
	git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

	checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;

	cl_git_pass(git_reference_lookup_resolved(&orig_ref, repo, "HEAD", 100));
	cl_git_pass(git_commit_lookup(&orig, repo, git_reference_target(orig_ref)));
	cl_git_pass(git_reset(repo, (git_object *)orig, GIT_RESET_HARD, NULL));

	cl_rename("testrepo/branch_file.txt", "testrepo/Branch_File.txt");

	cl_git_pass(git_reference_lookup_resolved(&br2_ref, repo, "refs/heads/br2", 100));
	cl_git_pass(git_commit_lookup(&br2, repo, git_reference_target(br2_ref)));

	cl_git_pass(git_checkout_tree(repo, (const git_object *)br2, &checkout_opts));

	git_commit_free(orig);
	git_commit_free(br2);
	git_reference_free(orig_ref);
	git_reference_free(br2_ref);
}