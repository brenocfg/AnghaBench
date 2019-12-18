#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_ (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char const*) ; 
 int git_futils_creat_withpath (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  git_futils_mkpath2file (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/ * git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/ * strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_repo_open__from_git_new_workdir(void)
{
#ifndef GIT_WIN32
	/* The git-new-workdir script that ships with git sets up a bunch of
	 * symlinks to create a second workdir that shares the object db with
	 * another checkout.  Libgit2 can open a repo that has been configured
	 * this way.
	 */

	git_repository *repo2;
	git_buf link_tgt = GIT_BUF_INIT, link = GIT_BUF_INIT, body = GIT_BUF_INIT;
	const char **scan;
	int link_fd;
	static const char *links[] = {
		"config", "refs", "logs/refs", "objects", "info", "hooks",
		"packed-refs", "remotes", "rr-cache", "svn", NULL
	};
	static const char *copies[] = {
		"HEAD", NULL
	};

	cl_git_sandbox_init("empty_standard_repo");

	cl_git_pass(p_mkdir("alternate", 0777));
	cl_git_pass(p_mkdir("alternate/.git", 0777));

	for (scan = links; *scan != NULL; scan++) {
		git_buf_joinpath(&link_tgt, "empty_standard_repo/.git", *scan);
		if (git_path_exists(link_tgt.ptr)) {
			git_buf_joinpath(&link_tgt, "../../empty_standard_repo/.git", *scan);
			git_buf_joinpath(&link, "alternate/.git", *scan);
			if (strchr(*scan, '/'))
				git_futils_mkpath2file(link.ptr, 0777);
			cl_assert_(symlink(link_tgt.ptr, link.ptr) == 0, strerror(errno));
		}
	}
	for (scan = copies; *scan != NULL; scan++) {
		git_buf_joinpath(&link_tgt, "empty_standard_repo/.git", *scan);
		if (git_path_exists(link_tgt.ptr)) {
			git_buf_joinpath(&link, "alternate/.git", *scan);
			cl_git_pass(git_futils_readbuffer(&body, link_tgt.ptr));

			cl_assert((link_fd = git_futils_creat_withpath(link.ptr, 0777, 0666)) >= 0);
			cl_must_pass(p_write(link_fd, body.ptr, body.size));
			p_close(link_fd);
		}
	}

	git_buf_dispose(&link_tgt);
	git_buf_dispose(&link);
	git_buf_dispose(&body);


	cl_git_pass(git_repository_open(&repo2, "alternate"));

	cl_assert(git_repository_path(repo2) != NULL);
	cl_assert_(git__suffixcmp(git_repository_path(repo2), "alternate/.git/") == 0, git_repository_path(repo2));

	cl_assert(git_repository_workdir(repo2) != NULL);
	cl_assert_(git__suffixcmp(git_repository_workdir(repo2), "alternate/") == 0, git_repository_workdir(repo2));

	git_repository_free(repo2);
#else
	cl_skip();
#endif
}