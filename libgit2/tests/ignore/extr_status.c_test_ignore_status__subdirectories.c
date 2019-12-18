#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ status_entry_single ;
typedef  int /*<<< orphan*/  st ;

/* Variables and functions */
 scalar_t__ GIT_STATUS_IGNORED ; 
 int /*<<< orphan*/  assert_is_ignored (char*) ; 
 int /*<<< orphan*/  cb_status__single ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 int /*<<< orphan*/  git_status_file (scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_status_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_ignore_status__subdirectories(void)
{
	status_entry_single st;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_mkfile(
		"empty_standard_repo/ignore_me", "I'm going to be ignored!");

	cl_git_rewritefile("empty_standard_repo/.gitignore", "ignore_me\n");

	memset(&st, 0, sizeof(st));
	cl_git_pass(git_status_foreach(g_repo, cb_status__single, &st));
	cl_assert_equal_i(2, st.count);
	cl_assert(st.status == GIT_STATUS_IGNORED);

	cl_git_pass(git_status_file(&st.status, g_repo, "ignore_me"));
	cl_assert(st.status == GIT_STATUS_IGNORED);

	assert_is_ignored("ignore_me");

	/* I've changed libgit2 so that the behavior here now differs from
	 * core git but seems to make more sense.  In core git, the following
	 * items are skipped completed, even if --ignored is passed to status.
	 * It you mirror these steps and run "git status -uall --ignored" then
	 * you will not see "test/ignore_me/" in the results.
	 *
	 * However, we had a couple reports of this as a bug, plus there is a
	 * similar circumstance where we were differing for core git when you
	 * used a rooted path for an ignore, so I changed this behavior.
	 */
	cl_git_pass(git_futils_mkdir_r(
		"empty_standard_repo/test/ignore_me", 0775));
	cl_git_mkfile(
		"empty_standard_repo/test/ignore_me/file", "I'm going to be ignored!");
	cl_git_mkfile(
		"empty_standard_repo/test/ignore_me/file2", "Me, too!");

	memset(&st, 0, sizeof(st));
	cl_git_pass(git_status_foreach(g_repo, cb_status__single, &st));
	cl_assert_equal_i(3, st.count);

	cl_git_pass(git_status_file(&st.status, g_repo, "test/ignore_me/file"));
	cl_assert(st.status == GIT_STATUS_IGNORED);

	assert_is_ignored("test/ignore_me/file");
}