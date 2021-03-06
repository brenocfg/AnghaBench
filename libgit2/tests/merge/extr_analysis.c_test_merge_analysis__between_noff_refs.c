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

/* Variables and functions */
 int /*<<< orphan*/  FASTFORWARD_BRANCH ; 
 int /*<<< orphan*/  GIT_MERGE_ANALYSIS_NORMAL ; 
 int /*<<< orphan*/  analysis_from_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_merge_analysis__between_noff_refs(void)
{
	git_merge_analysis_t merge_analysis;
	git_merge_preference_t merge_pref;

	analysis_from_branch(&merge_analysis, &merge_pref, "branch", FASTFORWARD_BRANCH);
	cl_assert_equal_i(GIT_MERGE_ANALYSIS_NORMAL, merge_analysis);
}