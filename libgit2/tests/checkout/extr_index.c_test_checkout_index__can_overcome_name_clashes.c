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
struct TYPE_4__ {int checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int GIT_CHECKOUT_ALLOW_CONFLICTS ; 
 int GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_checkout_index__can_overcome_name_clashes(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_index *index;

	cl_git_pass(git_repository_index(&index, g_repo));
	git_index_clear(index);

	cl_git_mkfile("./testrepo/path0", "content\r\n");
	cl_git_pass(p_mkdir("./testrepo/path1", 0777));
	cl_git_mkfile("./testrepo/path1/file1", "content\r\n");

	cl_git_pass(git_index_add_bypath(index, "path0"));
	cl_git_pass(git_index_add_bypath(index, "path1/file1"));

	cl_git_pass(p_unlink("./testrepo/path0"));
	cl_git_pass(git_futils_rmdir_r(
		"./testrepo/path1", NULL, GIT_RMDIR_REMOVE_FILES));

	cl_git_mkfile("./testrepo/path1", "content\r\n");
	cl_git_pass(p_mkdir("./testrepo/path0", 0777));
	cl_git_mkfile("./testrepo/path0/file0", "content\r\n");

	cl_assert(git_path_isfile("./testrepo/path1"));
	cl_assert(git_path_isfile("./testrepo/path0/file0"));

	opts.checkout_strategy =
		GIT_CHECKOUT_SAFE |
		GIT_CHECKOUT_RECREATE_MISSING |
		GIT_CHECKOUT_ALLOW_CONFLICTS;
	cl_git_pass(git_checkout_index(g_repo, index, &opts));

	cl_assert(git_path_isfile("./testrepo/path1"));
	cl_assert(git_path_isfile("./testrepo/path0/file0"));

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	cl_git_pass(git_checkout_index(g_repo, index, &opts));

	cl_assert(git_path_isfile("./testrepo/path0"));
	cl_assert(git_path_isfile("./testrepo/path1/file1"));

	git_index_free(index);
}