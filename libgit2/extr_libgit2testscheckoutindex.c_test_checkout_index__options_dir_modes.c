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
struct stat {int st_mode; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_4__ {int checkout_strategy; int dir_mode; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int GIT_FILEMODE_BLOB_EXECUTABLE ; 
 int GIT_FILEMODE_TREE ; 
 int S_IFMT ; 
 int /*<<< orphan*/  cl_assert_equal_i_fmt (int,int,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_chmod_supported () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 
 int p_umask (int) ; 
 int /*<<< orphan*/  reset_index_to_treeish (int /*<<< orphan*/ *) ; 

void test_checkout_index__options_dir_modes(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	struct stat st;
	git_oid oid;
	git_commit *commit;
	mode_t um;

	if (!cl_is_chmod_supported())
		return;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/dir"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &oid));

	reset_index_to_treeish((git_object *)commit);

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_RECREATE_MISSING;
	opts.dir_mode = 0701;

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	/* umask will influence actual directory creation mode */
	(void)p_umask(um = p_umask(022));

	cl_git_pass(p_stat("./testrepo/a", &st));
	/* Haiku & Hurd use other mode bits, so we must mask them out */
	cl_assert_equal_i_fmt(st.st_mode & (S_IFMT | 07777), (GIT_FILEMODE_TREE | 0701) & ~um, "%07o");

	/* File-mode test, since we're on the 'dir' branch */
	cl_git_pass(p_stat("./testrepo/a/b.txt", &st));
	cl_assert_equal_i_fmt(st.st_mode & (S_IFMT | 07777), GIT_FILEMODE_BLOB_EXECUTABLE & ~um, "%07o");

	git_commit_free(commit);
}