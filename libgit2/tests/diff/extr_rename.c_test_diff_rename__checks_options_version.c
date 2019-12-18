#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_9__ {int /*<<< orphan*/  klass; } ;
typedef  TYPE_1__ git_error ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ git_diff_options ;
struct TYPE_11__ {int version; } ;
typedef  TYPE_3__ git_diff_find_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 char* COPY_RENAME_COMMIT ; 
 TYPE_3__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNMODIFIED ; 
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 char* INITIAL_COMMIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_rename__checks_options_version(void)
{
	const char *old_sha = INITIAL_COMMIT;
	const char *new_sha = COPY_RENAME_COMMIT;
	git_tree *old_tree, *new_tree;
	git_diff *diff;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options opts = GIT_DIFF_FIND_OPTIONS_INIT;
	const git_error *err;

	old_tree = resolve_commit_oid_to_tree(g_repo, old_sha);
	new_tree = resolve_commit_oid_to_tree(g_repo, new_sha);
	diffopts.flags |= GIT_DIFF_INCLUDE_UNMODIFIED;
	cl_git_pass(git_diff_tree_to_tree(
		&diff, g_repo, old_tree, new_tree, &diffopts));

	opts.version = 0;
	cl_git_fail(git_diff_find_similar(diff, &opts));
	err = git_error_last();
	cl_assert_equal_i(GIT_ERROR_INVALID, err->klass);

	git_error_clear();
	opts.version = 1024;
	cl_git_fail(git_diff_find_similar(diff, &opts));
	err = git_error_last();
	cl_assert_equal_i(GIT_ERROR_INVALID, err->klass);

	git_diff_free(diff);
	git_tree_free(old_tree);
	git_tree_free(new_tree);
}