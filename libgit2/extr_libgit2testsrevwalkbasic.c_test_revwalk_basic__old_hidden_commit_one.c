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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_revwalk_hide (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (char*) ; 

void test_revwalk_basic__old_hidden_commit_one(void)
{
	git_oid new_id, old_id, oid;

	revwalk_basic_setup_walk("testrepo.git");

	cl_git_pass(git_oid_fromstr(&new_id, "bd758010071961f28336333bc41e9c64c9a64866"));
	cl_git_pass(git_revwalk_push(_walk, &new_id));

	cl_git_pass(git_oid_fromstr(&old_id, "8e73b769e97678d684b809b163bebdae2911720f"));
	cl_git_pass(git_revwalk_hide(_walk, &old_id));

	cl_git_pass(git_revwalk_next(&oid, _walk));
	cl_assert(!git_oid_streq(&oid, "bd758010071961f28336333bc41e9c64c9a64866"));

	cl_git_fail_with(GIT_ITEROVER, git_revwalk_next(&oid, _walk));
}