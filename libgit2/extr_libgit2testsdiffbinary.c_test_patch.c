#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_print_callback__to_buf ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_patch(
	const char *one,
	const char *two,
	const git_diff_options *opts,
	const char *expected)
{
	git_oid id_one, id_two;
	git_index *index = NULL;
	git_commit *commit_one, *commit_two = NULL;
	git_tree *tree_one, *tree_two;
	git_diff *diff;
	git_patch *patch;
	git_buf actual = GIT_BUF_INIT;

	cl_git_pass(git_oid_fromstr(&id_one, one));
	cl_git_pass(git_commit_lookup(&commit_one, repo, &id_one));
	cl_git_pass(git_commit_tree(&tree_one, commit_one));

	if (two) {
		cl_git_pass(git_oid_fromstr(&id_two, two));
		cl_git_pass(git_commit_lookup(&commit_two, repo, &id_two));
		cl_git_pass(git_commit_tree(&tree_two, commit_two));
	} else {
		cl_git_pass(git_repository_index(&index, repo));
		cl_git_pass(git_index_write_tree(&id_two, index));
		cl_git_pass(git_tree_lookup(&tree_two, repo, &id_two));
	}

	cl_git_pass(git_diff_tree_to_tree(&diff, repo, tree_one, tree_two, opts));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&actual, patch));

	cl_assert_equal_s(expected, actual.ptr);

	git_buf_clear(&actual);
	cl_git_pass(git_diff_print(diff, GIT_DIFF_FORMAT_PATCH, git_diff_print_callback__to_buf, &actual));

	cl_assert_equal_s(expected, actual.ptr);

	git_buf_dispose(&actual);
	git_patch_free(patch);
	git_diff_free(diff);
	git_tree_free(tree_one);
	git_tree_free(tree_two);
	git_commit_free(commit_one);
	git_commit_free(commit_two);
	git_index_free(index);
}