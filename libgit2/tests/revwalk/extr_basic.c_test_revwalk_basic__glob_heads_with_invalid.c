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
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push_glob (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (char*) ; 

void test_revwalk_basic__glob_heads_with_invalid(void)
{
	int i;
	git_oid oid;

	revwalk_basic_setup_walk("testrepo");

	cl_git_mkfile("testrepo/.git/refs/heads/garbage", "not-a-ref");
	cl_git_pass(git_revwalk_push_glob(_walk, "heads"));

	for (i = 0; !git_revwalk_next(&oid, _walk); ++i)
		/* walking */;

	/* git log --branches --oneline | wc -l => 16 */
	cl_assert_equal_i(20, i);
}