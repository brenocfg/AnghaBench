#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_worktree ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_WORKTREE ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 char* git_path_basename (char const*) ; 
 int git_path_prettify_dir (TYPE_1__*,char*,char const*) ; 
 char* git_repository_commondir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_worktree (int /*<<< orphan*/ *) ; 
 char* git_repository_path (int /*<<< orphan*/ *) ; 
 int open_worktree_dir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char*) ; 

int git_worktree_open_from_repository(git_worktree **out, git_repository *repo)
{
	git_buf parent = GIT_BUF_INIT;
	const char *gitdir, *commondir;
	char *name = NULL;
	int error = 0;

	if (!git_repository_is_worktree(repo)) {
		git_error_set(GIT_ERROR_WORKTREE, "cannot open worktree of a non-worktree repo");
		error = -1;
		goto out;
	}

	gitdir = git_repository_path(repo);
	commondir = git_repository_commondir(repo);

	if ((error = git_path_prettify_dir(&parent, "..", commondir)) < 0)
		goto out;

	/* The name is defined by the last component in '.git/worktree/%s' */
	name = git_path_basename(gitdir);

	if ((error = open_worktree_dir(out, parent.ptr, gitdir, name)) < 0)
		goto out;

out:
	git__free(name);
	git_buf_dispose(&parent);

	return error;
}