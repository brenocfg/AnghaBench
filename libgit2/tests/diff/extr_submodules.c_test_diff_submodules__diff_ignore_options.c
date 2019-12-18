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
struct TYPE_4__ {char* old_prefix; char* new_prefix; scalar_t__ ignore_submodules; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_IGNORE_SUBMODULES ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 scalar_t__ GIT_SUBMODULE_IGNORE_ALL ; 
 scalar_t__ GIT_SUBMODULE_IGNORE_DIRTY ; 
 int /*<<< orphan*/  check_diff_patches (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_fixture_submod2 () ; 

void test_diff_submodules__diff_ignore_options(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_config *cfg;
	static const char *expected_normal[] = {
		"<SKIP>", /* .gitmodules */
		"<UNTRACKED>", /* not-submodule */
		"<UNTRACKED>", /* not */
		"diff --git a/sm_changed_file b/sm_changed_file\nindex 4800958..4800958 160000\n--- a/sm_changed_file\n+++ b/sm_changed_file\n@@ -1 +1 @@\n-Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0\n+Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0-dirty\n", /* sm_changed_file */
		"diff --git a/sm_changed_head b/sm_changed_head\nindex 4800958..3d9386c 160000\n--- a/sm_changed_head\n+++ b/sm_changed_head\n@@ -1 +1 @@\n-Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0\n+Subproject commit 3d9386c507f6b093471a3e324085657a3c2b4247\n", /* sm_changed_head */
		"diff --git a/sm_changed_index b/sm_changed_index\nindex 4800958..4800958 160000\n--- a/sm_changed_index\n+++ b/sm_changed_index\n@@ -1 +1 @@\n-Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0\n+Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0-dirty\n", /* sm_changed_index */
		"diff --git a/sm_changed_untracked_file b/sm_changed_untracked_file\nindex 4800958..4800958 160000\n--- a/sm_changed_untracked_file\n+++ b/sm_changed_untracked_file\n@@ -1 +1 @@\n-Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0\n+Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0-dirty\n", /* sm_changed_untracked_file */
		"diff --git a/sm_missing_commits b/sm_missing_commits\nindex 4800958..5e49635 160000\n--- a/sm_missing_commits\n+++ b/sm_missing_commits\n@@ -1 +1 @@\n-Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0\n+Subproject commit 5e4963595a9774b90524d35a807169049de8ccad\n", /* sm_missing_commits */
		"<END>"
	};
	static const char *expected_ignore_all[] = {
		"<SKIP>", /* .gitmodules */
		"<UNTRACKED>", /* not-submodule */
		"<UNTRACKED>", /* not */
		"<END>"
	};
	static const char *expected_ignore_dirty[] = {
		"<SKIP>", /* .gitmodules */
		"<UNTRACKED>", /* not-submodule */
		"<UNTRACKED>", /* not */
		"diff --git a/sm_changed_head b/sm_changed_head\nindex 4800958..3d9386c 160000\n--- a/sm_changed_head\n+++ b/sm_changed_head\n@@ -1 +1 @@\n-Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0\n+Subproject commit 3d9386c507f6b093471a3e324085657a3c2b4247\n", /* sm_changed_head */
		"diff --git a/sm_missing_commits b/sm_missing_commits\nindex 4800958..5e49635 160000\n--- a/sm_missing_commits\n+++ b/sm_missing_commits\n@@ -1 +1 @@\n-Subproject commit 480095882d281ed676fe5b863569520e54a7d5c0\n+Subproject commit 5e4963595a9774b90524d35a807169049de8ccad\n", /* sm_missing_commits */
		"<END>"
	};

	g_repo = setup_fixture_submod2();

	opts.flags = GIT_DIFF_INCLUDE_UNTRACKED;
	opts.old_prefix = "a"; opts.new_prefix = "b";

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	check_diff_patches(diff, expected_normal);
	git_diff_free(diff);

	opts.flags |= GIT_DIFF_IGNORE_SUBMODULES;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	check_diff_patches(diff, expected_ignore_all);
	git_diff_free(diff);

	opts.flags &= ~GIT_DIFF_IGNORE_SUBMODULES;
	opts.ignore_submodules = GIT_SUBMODULE_IGNORE_ALL;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	check_diff_patches(diff, expected_ignore_all);
	git_diff_free(diff);

	opts.ignore_submodules = GIT_SUBMODULE_IGNORE_DIRTY;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	check_diff_patches(diff, expected_ignore_dirty);
	git_diff_free(diff);

	opts.ignore_submodules = 0;
	cl_git_pass(git_repository_config(&cfg, g_repo));
	cl_git_pass(git_config_set_bool(cfg, "diff.ignoreSubmodules", false));

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	check_diff_patches(diff, expected_normal);
	git_diff_free(diff);

	cl_git_pass(git_config_set_bool(cfg, "diff.ignoreSubmodules", true));

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	check_diff_patches(diff, expected_ignore_all);
	git_diff_free(diff);

	cl_git_pass(git_config_set_string(cfg, "diff.ignoreSubmodules", "none"));

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	check_diff_patches(diff, expected_normal);
	git_diff_free(diff);

	cl_git_pass(git_config_set_string(cfg, "diff.ignoreSubmodules", "dirty"));

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	check_diff_patches(diff, expected_ignore_dirty);
	git_diff_free(diff);

	git_config_free(cfg);
}