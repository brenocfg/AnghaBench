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
typedef  int git_merge_preference_t ;
typedef  int git_merge_analysis_t ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  FASTFORWARD_BRANCH ; 
 int GIT_MERGE_ANALYSIS_FASTFORWARD ; 
 int GIT_MERGE_ANALYSIS_NORMAL ; 
 int GIT_MERGE_PREFERENCE_NO_FASTFORWARD ; 
 int /*<<< orphan*/  analysis_from_branch (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_analysis__fastforward_with_config_noff(void)
{
	git_config *config;
	git_merge_analysis_t merge_analysis;
	git_merge_preference_t merge_pref;

	cl_git_pass(git_repository_config(&config, repo));
	cl_git_pass(git_config_set_string(config, "merge.ff", "false"));

	analysis_from_branch(&merge_analysis, &merge_pref, NULL, FASTFORWARD_BRANCH);
	cl_assert_equal_i(GIT_MERGE_ANALYSIS_NORMAL|GIT_MERGE_ANALYSIS_FASTFORWARD, merge_analysis);

	cl_assert_equal_i(GIT_MERGE_PREFERENCE_NO_FASTFORWARD, (merge_pref & GIT_MERGE_PREFERENCE_NO_FASTFORWARD));

	git_config_free(config);
}