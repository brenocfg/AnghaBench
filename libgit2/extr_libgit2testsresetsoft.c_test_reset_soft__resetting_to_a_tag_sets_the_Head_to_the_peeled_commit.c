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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_SOFT ; 
 int /*<<< orphan*/  KNOWN_COMMIT_IN_BARE_REPO ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int git_repository_head_detached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  target ; 

void test_reset_soft__resetting_to_a_tag_sets_the_Head_to_the_peeled_commit(void)
{
	git_oid oid;

	/* b25fa35 is a tag, pointing to another tag which points to commit e90810b */
	cl_git_pass(git_revparse_single(&target, repo, "b25fa35"));

	cl_git_pass(git_reset(repo, target, GIT_RESET_SOFT, NULL));

	cl_assert(git_repository_head_detached(repo) == false);
	cl_git_pass(git_reference_name_to_id(&oid, repo, "HEAD"));
	cl_git_pass(git_oid_streq(&oid, KNOWN_COMMIT_IN_BARE_REPO));
}