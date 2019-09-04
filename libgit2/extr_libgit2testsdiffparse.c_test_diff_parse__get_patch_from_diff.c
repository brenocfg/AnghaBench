#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_SHOW_BINARY ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_to_buf (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_num_hunks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ *,char*) ; 

void test_diff_parse__get_patch_from_diff(void)
{
	git_repository *repo;
	git_diff *computed, *parsed;
	git_tree *a, *b;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_buf computed_buf = GIT_BUF_INIT;
	git_patch *patch_computed, *patch_parsed;

	repo = cl_git_sandbox_init("diff");

	opts.flags = GIT_DIFF_SHOW_BINARY;

	cl_assert((a = resolve_commit_oid_to_tree(repo,
		"d70d245ed97ed2aa596dd1af6536e4bfdb047b69")) != NULL);
	cl_assert((b = resolve_commit_oid_to_tree(repo,
		"7a9e0b02e63179929fed24f0a3e0f19168114d10")) != NULL);

	cl_git_pass(git_diff_tree_to_tree(&computed, repo, a, b, &opts));
	cl_git_pass(git_diff_to_buf(&computed_buf,
		computed, GIT_DIFF_FORMAT_PATCH));
	cl_git_pass(git_patch_from_diff(&patch_computed, computed, 0));

	cl_git_pass(git_diff_from_buffer(&parsed,
		computed_buf.ptr, computed_buf.size));
	cl_git_pass(git_patch_from_diff(&patch_parsed, parsed, 0));

	cl_assert_equal_i(
		git_patch_num_hunks(patch_computed),
		git_patch_num_hunks(patch_parsed));

	git_patch_free(patch_computed);
	git_patch_free(patch_parsed);

	git_tree_free(a);
	git_tree_free(b);

	git_diff_free(computed);
	git_diff_free(parsed);

	git_buf_dispose(&computed_buf);

	cl_git_sandbox_cleanup();
}