#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_18__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
struct TYPE_19__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ git_diff_find_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_20__ {int size; scalar_t__ ptr; } ;
typedef  TYPE_3__ git_buf ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_21__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_4__ diff_expects ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_COPIED ; 
 size_t GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_ALL ; 
 TYPE_2__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNMODIFIED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_consume (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_3__*,int) ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  git_futils_writebuffer (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void test_diff_rename__rename_and_copy_from_same_source(void)
{
	git_buf c1 = GIT_BUF_INIT, c2 = GIT_BUF_INIT;
	git_index *index;
	git_tree *tree;
	git_diff *diff;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options opts = GIT_DIFF_FIND_OPTIONS_INIT;
	diff_expects exp;

	/* put the first 2/3 of file into one new place
	 * and the second 2/3 of file into another new place
	 */
	cl_git_pass(git_futils_readbuffer(&c1, "renames/songof7cities.txt"));
	cl_git_pass(git_buf_set(&c2, c1.ptr, c1.size));
	git_buf_truncate(&c1, c1.size * 2 / 3);
	git_buf_consume(&c2, ((char *)c2.ptr) + (c2.size / 3));
	cl_git_pass(git_futils_writebuffer(&c1, "renames/song_a.txt", 0, 0));
	cl_git_pass(git_futils_writebuffer(&c2, "renames/song_b.txt", 0, 0));

	cl_git_pass(
		git_revparse_single((git_object **)&tree, g_repo, "HEAD^{tree}"));

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_read_tree(index, tree));
	cl_git_pass(git_index_add_bypath(index, "song_a.txt"));
	cl_git_pass(git_index_add_bypath(index, "song_b.txt"));

	diffopts.flags = GIT_DIFF_INCLUDE_UNMODIFIED;

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, tree, index, &diffopts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(6, exp.files);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_UNMODIFIED]);

	opts.flags = GIT_DIFF_FIND_ALL;
	cl_git_pass(git_diff_find_similar(diff, &opts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(6, exp.files);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_COPIED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_UNMODIFIED]);

	git_diff_free(diff);
	git_tree_free(tree);
	git_index_free(index);

	git_buf_dispose(&c1);
	git_buf_dispose(&c2);
}