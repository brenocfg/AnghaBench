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
 int /*<<< orphan*/  GIT_DIFF_STATS_FULL ; 
 int /*<<< orphan*/  _stats ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_stats_from_commit_oid (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_stats_deletions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_stats_files_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_stats_insertions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_stats_to_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_diff_stats__multiple_hunks(void)
{
	git_buf buf = GIT_BUF_INIT;
	const char *stat =
	" file2.txt | 5 +++--\n" \
	" file3.txt | 6 ++++--\n" \
	" 2 files changed, 7 insertions(+), 4 deletions(-)\n";

	diff_stats_from_commit_oid(
		&_stats, "cd471f0d8770371e1bc78bcbb38db4c7e4106bd2", false);

	cl_assert_equal_sz(2, git_diff_stats_files_changed(_stats));
	cl_assert_equal_sz(7, git_diff_stats_insertions(_stats));
	cl_assert_equal_sz(4, git_diff_stats_deletions(_stats));

	cl_git_pass(git_diff_stats_to_buf(&buf, _stats, GIT_DIFF_STATS_FULL, 0));
	cl_assert_equal_s(stat, git_buf_cstr(&buf));
	git_buf_dispose(&buf);
}