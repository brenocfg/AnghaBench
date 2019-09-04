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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_branch () ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_workdir_dirty__unstaged_deletes_maintained(void)
{
	git_reference *head;
	git_object *head_object;

	cl_git_pass(git_repository_head(&head, repo));
	cl_git_pass(git_reference_peel(&head_object, head, GIT_OBJECT_COMMIT));
	cl_git_pass(git_reset(repo, head_object, GIT_RESET_HARD, NULL));

	cl_git_pass(p_unlink("merge-resolve/unchanged.txt"));

	cl_git_pass(merge_branch());

	git_object_free(head_object);
	git_reference_free(head);
}