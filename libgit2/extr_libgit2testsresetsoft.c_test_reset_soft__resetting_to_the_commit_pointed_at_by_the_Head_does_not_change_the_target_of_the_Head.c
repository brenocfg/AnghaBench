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
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  GIT_RESET_SOFT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  target ; 

void test_reset_soft__resetting_to_the_commit_pointed_at_by_the_Head_does_not_change_the_target_of_the_Head(void)
{
	git_oid oid;
	char raw_head_oid[GIT_OID_HEXSZ + 1];

	cl_git_pass(git_reference_name_to_id(&oid, repo, "HEAD"));
	git_oid_fmt(raw_head_oid, &oid);
	raw_head_oid[GIT_OID_HEXSZ] = '\0';

	cl_git_pass(git_revparse_single(&target, repo, raw_head_oid));

	cl_git_pass(git_reset(repo, target, GIT_RESET_SOFT, NULL));

	cl_git_pass(git_reference_name_to_id(&oid, repo, "HEAD"));
	cl_git_pass(git_oid_streq(&oid, raw_head_oid));
}