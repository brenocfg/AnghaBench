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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * failing_commit_cases ; 
 scalar_t__ git__prefixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_commit__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_commit (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * passing_commit_cases ; 

void test_commit_parse__entire_commit(void)
{
	const int failing_commit_count = ARRAY_SIZE(failing_commit_cases);
	const int passing_commit_count = ARRAY_SIZE(passing_commit_cases);
	int i;
	git_commit *commit;

	for (i = 0; i < failing_commit_count; ++i) {
		cl_git_fail(parse_commit(&commit, failing_commit_cases[i]));
		git_commit__free(commit);
	}

	for (i = 0; i < passing_commit_count; ++i) {
		cl_git_pass(parse_commit(&commit, passing_commit_cases[i]));

		if (!i)
			cl_assert_equal_s("", git_commit_message(commit));
		else
			cl_assert(git__prefixcmp(
				git_commit_message(commit), "a simple commit which works") == 0);

		git_commit__free(commit);
	}
}