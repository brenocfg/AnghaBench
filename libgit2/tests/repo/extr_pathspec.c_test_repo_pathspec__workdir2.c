#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  strings; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_pathspec_match_list ;
typedef  int /*<<< orphan*/  git_pathspec ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int GIT_PATHSPEC_FIND_FAILURES ; 
 int GIT_PATHSPEC_NO_GLOB ; 
 int GIT_PATHSPEC_NO_MATCH_ERROR ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_pathspec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_list_failed_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_new (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  str2 ; 

void test_repo_pathspec__workdir2(void)
{
	git_strarray s;
	git_pathspec *ps;
	git_pathspec_match_list *m;

	/* { "staged_*" } */
	s.strings = str2; s.count = ARRAY_SIZE(str2);
	cl_git_pass(git_pathspec_new(&ps, &s));

	cl_git_pass(git_pathspec_match_workdir(&m, g_repo, 0, ps));
	cl_assert_equal_sz(5, git_pathspec_match_list_entrycount(m));
	git_pathspec_match_list_free(m);

	cl_git_pass(git_pathspec_match_workdir(&m, g_repo,
		GIT_PATHSPEC_FIND_FAILURES, ps));
	cl_assert_equal_sz(5, git_pathspec_match_list_entrycount(m));
	cl_assert_equal_sz(0, git_pathspec_match_list_failed_entrycount(m));
	git_pathspec_match_list_free(m);

	cl_git_fail(git_pathspec_match_workdir(&m, g_repo,
		GIT_PATHSPEC_NO_GLOB | GIT_PATHSPEC_NO_MATCH_ERROR, ps));

	cl_git_pass(git_pathspec_match_workdir(&m, g_repo,
		GIT_PATHSPEC_NO_GLOB | GIT_PATHSPEC_FIND_FAILURES, ps));
	cl_assert_equal_sz(0, git_pathspec_match_list_entrycount(m));
	cl_assert_equal_sz(1, git_pathspec_match_list_failed_entrycount(m));
	git_pathspec_match_list_free(m);

	git_pathspec_free(ps);
}