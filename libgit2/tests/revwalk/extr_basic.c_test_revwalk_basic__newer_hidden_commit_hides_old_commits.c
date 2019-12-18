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
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_revwalk_hide_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (char*) ; 

void test_revwalk_basic__newer_hidden_commit_hides_old_commits(void)
{
	git_oid oid;

	revwalk_basic_setup_walk("revwalk.git");

	cl_git_pass(git_revwalk_push_ref(_walk, "refs/heads/D"));
	cl_git_pass(git_revwalk_hide_ref(_walk, "refs/heads/B"));
	cl_git_pass(git_revwalk_hide_ref(_walk, "refs/heads/A"));
	cl_git_pass(git_revwalk_hide_ref(_walk, "refs/heads/E"));

	cl_git_pass(git_revwalk_next(&oid, _walk));
	cl_assert(git_oid_streq(&oid, "b82cee5004151ae0c4f82b69fb71b87477664b6f"));
	cl_git_pass(git_revwalk_next(&oid, _walk));
	cl_assert(git_oid_streq(&oid, "790ba0facf6fd103699a5c40cd19dad277ff49cd"));

	cl_git_fail_with(GIT_ITEROVER, git_revwalk_next(&oid, _walk));
}