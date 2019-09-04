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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  commit ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int git_commit_nth_gen_ancestor (int /*<<< orphan*/ **,int /*<<< orphan*/ ,unsigned int) ; 
 int git_oid_streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void assert_nth_gen_parent(unsigned int gen, const char *expected_oid)
{
	git_commit *parent = NULL;
	int error;
	
	error = git_commit_nth_gen_ancestor(&parent, commit, gen);

	if (expected_oid != NULL) {
		cl_assert_equal_i(0, error);
		cl_assert_equal_i(0, git_oid_streq(git_commit_id(parent), expected_oid));
	} else
		cl_assert_equal_i(GIT_ENOTFOUND, error);

	git_commit_free(parent);
}