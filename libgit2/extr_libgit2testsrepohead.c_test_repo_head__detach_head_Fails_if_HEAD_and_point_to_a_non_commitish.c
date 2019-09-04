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
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_detach_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_repo_head__detach_head_Fails_if_HEAD_and_point_to_a_non_commitish(void)
{
	git_reference *head;

	cl_git_pass(git_reference_symbolic_create(&head, repo, GIT_HEAD_FILE, "refs/tags/point_to_blob", 1, NULL));

	cl_git_fail(git_repository_detach_head(repo));

	git_reference_free(head);
}