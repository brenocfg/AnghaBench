#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_SYMLINKS ; 
 int S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_workdir_contents (char const*,char const*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int p_readlink (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static void ensure_workdir_link(
	git_repository *repo,
	const char *path,
	const char *target)
{
	int symlinks;

	cl_git_pass(git_repository__configmap_lookup(&symlinks, repo, GIT_CONFIGMAP_SYMLINKS));

	if (!symlinks) {
		ensure_workdir_contents(path, target);
	} else {
		git_buf fullpath = GIT_BUF_INIT;
		char actual[1024];
		struct stat st;
		int len;

		cl_git_pass(
			git_buf_joinpath(&fullpath, git_repository_workdir(g_repo), path));

		cl_git_pass(p_lstat(git_buf_cstr(&fullpath), &st));
		cl_assert(S_ISLNK(st.st_mode));

		cl_assert((len = p_readlink(git_buf_cstr(&fullpath), actual, 1024)) > 0);
		actual[len] = '\0';
		cl_assert(strcmp(actual, target) == 0);

		git_buf_dispose(&fullpath);
	}
}