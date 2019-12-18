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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_DIFF_STATS_FULL ; 
 int GIT_DIFF_STATS_INCLUDE_SUMMARY ; 
 int /*<<< orphan*/  _stats ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_stats_from_commit_oid (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_stats_to_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void test_diff_stats__mode_change(void)
{
	git_buf buf = GIT_BUF_INIT;
	const char *stat =
	" file1.txt.renamed | 0\n" \
	" 1 file changed, 0 insertions(+), 0 deletions(-)\n" \
		" mode change 100644 => 100755 file1.txt.renamed\n";

	diff_stats_from_commit_oid(
		&_stats, "7ade76dd34bba4733cf9878079f9fd4a456a9189", false);

	cl_git_pass(git_diff_stats_to_buf(&buf, _stats, GIT_DIFF_STATS_FULL | GIT_DIFF_STATS_INCLUDE_SUMMARY, 0));
	cl_assert_equal_s(stat, git_buf_cstr(&buf));
	git_buf_dispose(&buf);
}