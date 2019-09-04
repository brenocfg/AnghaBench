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
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_cb ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_parse__foreach_works_with_parsed_patch(void)
{
	const char patch[] =
	    "diff --git a/obj1 b/obj2\n"
	    "index 1234567..7654321 10644\n"
	    "--- a/obj1\n"
	    "+++ b/obj2\n"
	    "@@ -1 +1 @@\n"
	    "-abcde\n"
	    "+12345\n";
	int called = 0;
	git_diff *diff;

	cl_git_pass(git_diff_from_buffer(&diff, patch, strlen(patch)));
	cl_git_pass(git_diff_foreach(diff, file_cb, NULL, NULL, NULL, &called));
	cl_assert_equal_i(called, 1);

	git_diff_free(diff);
}