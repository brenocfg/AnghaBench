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
 scalar_t__ git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push_glob (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_revwalk_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (int /*<<< orphan*/ *) ; 

void test_revwalk_basic__push_mixed(void)
{
	git_oid oid;
	int i = 0;

	revwalk_basic_setup_walk(NULL);

	git_revwalk_reset(_walk);
	git_revwalk_sorting(_walk, 0);
	cl_git_pass(git_revwalk_push_glob(_walk, "tags"));

	while (git_revwalk_next(&oid, _walk) == 0) {
		i++;
	}

	/* git rev-list --count --glob=tags #=> 9 */
	cl_assert_equal_i(9, i);
}