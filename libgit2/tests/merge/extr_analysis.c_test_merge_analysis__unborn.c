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
typedef  int /*<<< orphan*/  git_merge_preference_t ;
typedef  int /*<<< orphan*/  git_merge_analysis_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_MERGE_ANALYSIS_FASTFORWARD ; 
 int GIT_MERGE_ANALYSIS_UNBORN ; 
 int /*<<< orphan*/  NOFASTFORWARD_BRANCH ; 
 int /*<<< orphan*/  analysis_from_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_analysis__unborn(void)
{
	git_merge_analysis_t merge_analysis;
	git_merge_preference_t merge_pref;
	git_buf master = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&master, git_repository_path(repo), "refs/heads/master"));
	cl_must_pass(p_unlink(git_buf_cstr(&master)));

	analysis_from_branch(&merge_analysis, &merge_pref, NULL, NOFASTFORWARD_BRANCH);
	cl_assert_equal_i(GIT_MERGE_ANALYSIS_FASTFORWARD|GIT_MERGE_ANALYSIS_UNBORN, merge_analysis);

	git_buf_dispose(&master);
}