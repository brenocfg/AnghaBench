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
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_assert_lineinfo (int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_get_hunk (int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_parse__issue4672(void)
{
	const char *text = "diff --git a/a b/a\n"
	"index 7f129fd..af431f2 100644\n"
	"--- a/a\n"
	"+++ b/a\n"
	"@@ -3 +3 @@\n"
	"-a contents 2\n"
	"+a contents\n";

	git_diff *diff;
	git_patch *patch;
	const git_diff_hunk *hunk;
	size_t n, l = 0;

	cl_git_pass(git_diff_from_buffer(&diff, text, strlen(text)));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_get_hunk(&hunk, &n, patch, 0));

	cl_git_assert_lineinfo(3, -1, 1, patch, 0, l++);
	cl_git_assert_lineinfo(-1, 3, 1, patch, 0, l++);

	cl_assert_equal_i(n, l);

	git_patch_free(patch);
	git_diff_free(diff);
}