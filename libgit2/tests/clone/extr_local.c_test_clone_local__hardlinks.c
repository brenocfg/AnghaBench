#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_nlink; } ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_9__ {int bare; void* local; } ;
typedef  TYPE_1__ git_clone_options ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 void* GIT_CLONE_LOCAL ; 
 void* GIT_CLONE_LOCAL_NO_LINKS ; 
 TYPE_1__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 char* cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 char* cl_git_path_url (char*) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_join_n (TYPE_2__*,char,int,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,char*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_stat (int /*<<< orphan*/ ,struct stat*) ; 

void test_clone_local__hardlinks(void)
{
	git_repository *repo;
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	git_buf buf = GIT_BUF_INIT;
	struct stat st;

	/*
	 * In this first clone, we just copy over, since the temp dir
	 * will often be in a different filesystem, so we cannot
	 * link. It also allows us to control the number of links
	 */
	opts.bare = true;
	opts.local = GIT_CLONE_LOCAL_NO_LINKS;
	cl_git_pass(git_clone(&repo, cl_fixture("testrepo.git"), "./clone.git", &opts));
	git_repository_free(repo);

	/* This second clone is in the same filesystem, so we can hardlink */

	opts.local = GIT_CLONE_LOCAL;
	cl_git_pass(git_clone(&repo, cl_git_path_url("clone.git"), "./clone2.git", &opts));

#ifndef GIT_WIN32
	git_buf_clear(&buf);
	cl_git_pass(git_buf_join_n(&buf, '/', 4, git_repository_path(repo), "objects", "08", "b041783f40edfe12bb406c9c9a8a040177c125"));

	cl_git_pass(p_stat(buf.ptr, &st));
	cl_assert_equal_i(2, st.st_nlink);
#endif

	git_repository_free(repo);
	git_buf_clear(&buf);

	opts.local = GIT_CLONE_LOCAL_NO_LINKS;
	cl_git_pass(git_clone(&repo, cl_git_path_url("clone.git"), "./clone3.git", &opts));

	git_buf_clear(&buf);
	cl_git_pass(git_buf_join_n(&buf, '/', 4, git_repository_path(repo), "objects", "08", "b041783f40edfe12bb406c9c9a8a040177c125"));

	cl_git_pass(p_stat(buf.ptr, &st));
	cl_assert_equal_i(1, st.st_nlink);

	git_repository_free(repo);

	/* this one should automatically use links */
	cl_git_pass(git_clone(&repo, "./clone.git", "./clone4.git", NULL));

#ifndef GIT_WIN32
	git_buf_clear(&buf);
	cl_git_pass(git_buf_join_n(&buf, '/', 4, git_repository_path(repo), "objects", "08", "b041783f40edfe12bb406c9c9a8a040177c125"));

	cl_git_pass(p_stat(buf.ptr, &st));
	cl_assert_equal_i(3, st.st_nlink);
#endif

	git_buf_dispose(&buf);
	git_repository_free(repo);

	cl_git_pass(git_futils_rmdir_r("./clone.git", NULL, GIT_RMDIR_REMOVE_FILES));
	cl_git_pass(git_futils_rmdir_r("./clone2.git", NULL, GIT_RMDIR_REMOVE_FILES));
	cl_git_pass(git_futils_rmdir_r("./clone3.git", NULL, GIT_RMDIR_REMOVE_FILES));
	cl_git_pass(git_futils_rmdir_r("./clone4.git", NULL, GIT_RMDIR_REMOVE_FILES));
}