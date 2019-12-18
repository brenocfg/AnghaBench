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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_move (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_move__can_force_move_over_an_existing_branch(void)
{
	git_reference *original_ref, *new_ref;

	cl_git_pass(git_reference_lookup(&original_ref, repo, "refs/heads/br2"));

	cl_git_pass(git_branch_move(&new_ref, original_ref, "master", 1));

	git_reference_free(original_ref);
	git_reference_free(new_ref);
}