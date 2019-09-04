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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_hide_ref (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (int /*<<< orphan*/ *) ; 

void test_revwalk_basic__push_head_hide_ref(void)
{
	int i = 0;
	git_oid oid;

	revwalk_basic_setup_walk(NULL);

	cl_git_pass(git_revwalk_push_head(_walk));
	cl_git_pass(git_revwalk_hide_ref(_walk, "refs/heads/packed-test"));

	while (git_revwalk_next(&oid, _walk) == 0) {
		i++;
	}

	/* git log HEAD --oneline --not refs/heads/packed-test | wc -l => 4 */
	cl_assert_equal_i(i, 4);
}