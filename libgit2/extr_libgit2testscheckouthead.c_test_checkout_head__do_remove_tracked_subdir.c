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
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_checkout_head__do_remove_tracked_subdir(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_index *index;

	cl_git_pass(p_mkdir("testrepo/subdir", 0755));
	cl_git_pass(p_mkdir("testrepo/subdir/tracked", 0755));
	cl_git_mkfile("testrepo/subdir/tracked-file", "tracked\n");
	cl_git_mkfile("testrepo/subdir/untracked-file", "untracked\n");
	cl_git_mkfile("testrepo/subdir/tracked/tracked1", "tracked\n");
	cl_git_mkfile("testrepo/subdir/tracked/tracked2", "tracked\n");

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_add_bypath(index, "subdir/tracked-file"));
	cl_git_pass(git_index_add_bypath(index, "subdir/tracked/tracked1"));
	cl_git_pass(git_index_add_bypath(index, "subdir/tracked/tracked2"));
	cl_git_pass(git_index_write(index));

	git_index_free(index);

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	cl_git_pass(git_checkout_head(g_repo, &opts));

	cl_assert(!git_path_isdir("testrepo/subdir/tracked"));
	cl_assert(!git_path_isfile("testrepo/subdir/tracked-file"));
	cl_assert(git_path_isfile("testrepo/subdir/untracked-file"));
}