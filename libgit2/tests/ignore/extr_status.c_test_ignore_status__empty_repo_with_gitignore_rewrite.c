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
struct TYPE_4__ {int count; scalar_t__ status; } ;
typedef  TYPE_1__ status_entry_single ;
typedef  int /*<<< orphan*/  st ;

/* Variables and functions */
 scalar_t__ GIT_STATUS_IGNORED ; 
 scalar_t__ GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  assert_is_ignored (char*) ; 
 int /*<<< orphan*/  cb_status__single ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_status_file (scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_status_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refute_is_ignored (char*) ; 

void test_ignore_status__empty_repo_with_gitignore_rewrite(void)
{
	status_entry_single st;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_mkfile(
		"empty_standard_repo/look-ma.txt", "I'm going to be ignored!");

	memset(&st, 0, sizeof(st));
	cl_git_pass(git_status_foreach(g_repo, cb_status__single, &st));
	cl_assert(st.count == 1);
	cl_assert(st.status == GIT_STATUS_WT_NEW);

	cl_git_pass(git_status_file(&st.status, g_repo, "look-ma.txt"));
	cl_assert(st.status == GIT_STATUS_WT_NEW);

	refute_is_ignored("look-ma.txt");

	cl_git_rewritefile("empty_standard_repo/.gitignore", "*.nomatch\n");

	memset(&st, 0, sizeof(st));
	cl_git_pass(git_status_foreach(g_repo, cb_status__single, &st));
	cl_assert(st.count == 2);
	cl_assert(st.status == GIT_STATUS_WT_NEW);

	cl_git_pass(git_status_file(&st.status, g_repo, "look-ma.txt"));
	cl_assert(st.status == GIT_STATUS_WT_NEW);

	refute_is_ignored("look-ma.txt");

	cl_git_rewritefile("empty_standard_repo/.gitignore", "*.txt\n");

	memset(&st, 0, sizeof(st));
	cl_git_pass(git_status_foreach(g_repo, cb_status__single, &st));
	cl_assert(st.count == 2);
	cl_assert(st.status == GIT_STATUS_IGNORED);

	cl_git_pass(git_status_file(&st.status, g_repo, "look-ma.txt"));
	cl_assert(st.status == GIT_STATUS_IGNORED);

	assert_is_ignored("look-ma.txt");
}