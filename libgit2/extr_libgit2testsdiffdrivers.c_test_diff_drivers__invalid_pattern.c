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
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_diff_drivers__invalid_pattern(void)
{
	git_config *cfg;
	git_index *idx;
	git_diff *diff;
	git_patch *patch;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;

	g_repo = cl_git_sandbox_init("userdiff");
	cl_git_mkfile("userdiff/.gitattributes", "*.storyboard diff=storyboard\n");

	cl_git_pass(git_repository_config__weakptr(&cfg, g_repo));
	cl_git_pass(git_config_set_string(cfg, "diff.storyboard.xfuncname", "<!--(.*?)-->"));

	cl_git_mkfile("userdiff/dummy.storyboard", "");
	cl_git_pass(git_repository_index__weakptr(&idx, g_repo));
	cl_git_pass(git_index_add_bypath(idx, "dummy.storyboard"));
	cl_git_mkfile("userdiff/dummy.storyboard", "some content\n");

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));

	git_patch_free(patch);
	git_diff_free(diff);
}