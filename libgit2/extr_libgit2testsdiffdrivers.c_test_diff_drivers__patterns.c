#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_11__ {int /*<<< orphan*/ * diff_drivers; } ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_append2file (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 TYPE_2__* cl_git_sandbox_init (char*) ; 
 TYPE_2__* g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_diff_driver_registry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_workdir (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (TYPE_2__*,char const*) ; 

void test_diff_drivers__patterns(void)
{
	git_config *cfg;
	const char *one_sha = "19dd32dfb1520a64e5bbaae8dce6ef423dfa2f13";
	git_tree *one;
	git_diff *diff;
	git_patch *patch;
	git_buf actual = GIT_BUF_INIT;
	const char *expected0 = "diff --git a/untimely.txt b/untimely.txt\nindex 9a69d96..57fd0cf 100644\n--- a/untimely.txt\n+++ b/untimely.txt\n@@ -22,3 +22,5 @@ Comes through the blood of the vanguards who\n   dreamed--too soon--it had sounded.\r\n \r\n                 -- Rudyard Kipling\r\n+\r\n+Some new stuff\r\n";
	const char *expected1 = "diff --git a/untimely.txt b/untimely.txt\nindex 9a69d96..57fd0cf 100644\nBinary files a/untimely.txt and b/untimely.txt differ\n";
	const char *expected2 = "diff --git a/untimely.txt b/untimely.txt\nindex 9a69d96..57fd0cf 100644\n--- a/untimely.txt\n+++ b/untimely.txt\n@@ -22,3 +22,5 @@ Heaven delivers on earth the Hour that cannot be\n   dreamed--too soon--it had sounded.\r\n \r\n                 -- Rudyard Kipling\r\n+\r\n+Some new stuff\r\n";

	g_repo = cl_git_sandbox_init("renames");

	one = resolve_commit_oid_to_tree(g_repo, one_sha);

	/* no diff */

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, one, NULL));
	cl_assert_equal_i(0, (int)git_diff_num_deltas(diff));
	git_diff_free(diff);

	/* default diff */

	cl_git_append2file("renames/untimely.txt", "\r\nSome new stuff\r\n");

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, one, NULL));
	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&actual, patch));
	cl_assert_equal_s(expected0, actual.ptr);

	git_buf_dispose(&actual);
	git_patch_free(patch);
	git_diff_free(diff);

	/* attribute diff set to false */

	cl_git_rewritefile("renames/.gitattributes", "untimely.txt -diff\n");

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, one, NULL));
	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&actual, patch));
	cl_assert_equal_s(expected1, actual.ptr);

	git_buf_dispose(&actual);
	git_patch_free(patch);
	git_diff_free(diff);

	/* attribute diff set to unconfigured value (should use default) */

	cl_git_rewritefile("renames/.gitattributes", "untimely.txt diff=kipling0\n");

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, one, NULL));
	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&actual, patch));
	cl_assert_equal_s(expected0, actual.ptr);

	git_buf_dispose(&actual);
	git_patch_free(patch);
	git_diff_free(diff);

	/* let's define that driver */

	cl_git_pass(git_repository_config(&cfg, g_repo));
	cl_git_pass(git_config_set_bool(cfg, "diff.kipling0.binary", 1));
	git_config_free(cfg);

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, one, NULL));
	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&actual, patch));
	cl_assert_equal_s(expected1, actual.ptr);

	git_buf_dispose(&actual);
	git_patch_free(patch);
	git_diff_free(diff);

	/* let's use a real driver with some regular expressions */

	git_diff_driver_registry_free(g_repo->diff_drivers);
	g_repo->diff_drivers = NULL;

	cl_git_pass(git_repository_config(&cfg, g_repo));
	cl_git_pass(git_config_set_bool(cfg, "diff.kipling0.binary", 0));
	cl_git_pass(git_config_set_string(cfg, "diff.kipling0.xfuncname", "^H.*$"));
	git_config_free(cfg);

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, one, NULL));
	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&actual, patch));
	cl_assert_equal_s(expected2, actual.ptr);

	git_buf_dispose(&actual);
	git_patch_free(patch);
	git_diff_free(diff);

	git_tree_free(one);
}