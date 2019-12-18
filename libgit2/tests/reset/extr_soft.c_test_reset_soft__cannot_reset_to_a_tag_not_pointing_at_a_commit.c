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

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_SOFT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  target ; 

void test_reset_soft__cannot_reset_to_a_tag_not_pointing_at_a_commit(void)
{
	/* 53fc32d is the tree of commit e90810b */
	cl_git_pass(git_revparse_single(&target, repo, "53fc32d"));

	cl_git_fail(git_reset(repo, target, GIT_RESET_SOFT, NULL));
	git_object_free(target);

	/* 521d87c is an annotated tag pointing to a blob */
	cl_git_pass(git_revparse_single(&target, repo, "521d87c"));
	cl_git_fail(git_reset(repo, target, GIT_RESET_SOFT, NULL));
}