#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  length; scalar_t__ contents; } ;
typedef  TYPE_4__ git_vector ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_15__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_19__ {TYPE_1__ pathspec; } ;
typedef  TYPE_5__ git_diff_options ;
struct TYPE_17__ {int /*<<< orphan*/  mode; } ;
struct TYPE_16__ {int /*<<< orphan*/  mode; } ;
struct TYPE_20__ {TYPE_3__ new_file; TYPE_2__ old_file; } ;
typedef  TYPE_6__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_21__ {int /*<<< orphan*/  files; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ diff_expects ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIGMAP_SYMLINKS ; 
 TYPE_5__ GIT_DIFF_OPTIONS_INIT ; 
 int GIT_FILEMODE_LINK ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 TYPE_4__ GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_6__* git_diff_get_delta (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  git_futils_mkpath2file (char*,int) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_workdir (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_4__*) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_workdir__symlink_changed_on_non_symlink_platform(void)
{
	git_tree *tree;
	git_diff *diff;
	diff_expects exp = {0};
	const git_diff_delta *delta;
	const char *commit = "7fccd7";
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_vector pathlist = GIT_VECTOR_INIT;
	int symlinks;

	g_repo = cl_git_sandbox_init("unsymlinked.git");

	cl_git_pass(git_repository__configmap_lookup(&symlinks, g_repo, GIT_CONFIGMAP_SYMLINKS));

	if (symlinks)
		cl_skip();

	cl_git_pass(git_vector_insert(&pathlist, "include/Nu/Nu.h"));

	opts.pathspec.strings = (char **)pathlist.contents;
	opts.pathspec.count = pathlist.length;

	cl_must_pass(p_mkdir("symlink", 0777));
	cl_git_pass(git_repository_set_workdir(g_repo, "symlink", false));

	cl_assert((tree = resolve_commit_oid_to_tree(g_repo, commit)) != NULL);

	/* first, do the diff with the original contents */

	cl_git_pass(git_futils_mkpath2file("symlink/include/Nu/Nu.h", 0755));
	cl_git_mkfile("symlink/include/Nu/Nu.h", "../../objc/Nu.h");

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, tree, &opts));
	cl_assert_equal_i(0, git_diff_num_deltas(diff));
	git_diff_free(diff);

	/* now update the contents and expect a difference, but that the file
	 * mode has persisted as a symbolic link.
	 */

	cl_git_rewritefile("symlink/include/Nu/Nu.h", "awesome content\n");

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, tree, &opts));

	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(1, exp.files);

	cl_assert_equal_i(1, git_diff_num_deltas(diff));
	delta = git_diff_get_delta(diff, 0);
	cl_assert_equal_i(GIT_FILEMODE_LINK, delta->old_file.mode);
	cl_assert_equal_i(GIT_FILEMODE_LINK, delta->new_file.mode);

	git_diff_free(diff);

	cl_git_pass(git_futils_rmdir_r("symlink", NULL, GIT_RMDIR_REMOVE_FILES));

	git_tree_free(tree);
	git_vector_free(&pathlist);
}