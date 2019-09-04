#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_6__ {int /*<<< orphan*/  klass; } ;
typedef  TYPE_1__ git_error ;
struct TYPE_7__ {int version; } ;
typedef  TYPE_2__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_index__checks_options_version(void)
{
	const char *a_commit = "26a125ee1bf";
	git_tree *a = resolve_commit_oid_to_tree(g_repo, a_commit);
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	const git_error *err;

	opts.version = 0;
	cl_git_fail(git_diff_tree_to_index(&diff, g_repo, a, NULL, &opts));
	err = git_error_last();
	cl_assert_equal_i(GIT_ERROR_INVALID, err->klass);
	cl_assert_equal_p(diff, NULL);

	git_error_clear();
	opts.version = 1024;
	cl_git_fail(git_diff_tree_to_index(&diff, g_repo, a, NULL, &opts));
	err = git_error_last();
	cl_assert_equal_i(GIT_ERROR_INVALID, err->klass);
	cl_assert_equal_p(diff, NULL);

	git_tree_free(a);
}