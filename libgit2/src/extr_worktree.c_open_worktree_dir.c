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
struct TYPE_6__ {int locked; int /*<<< orphan*/  gitdir_path; int /*<<< orphan*/ * gitlink_path; int /*<<< orphan*/ * worktree_path; int /*<<< orphan*/ * parent_path; int /*<<< orphan*/ * commondir_path; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ git_worktree ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 TYPE_1__* git__calloc (int,int) ; 
 void* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_path_dirname (int /*<<< orphan*/ *) ; 
 int git_path_prettify_dir (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 void* git_worktree__read_link (char const*,char*) ; 
 int /*<<< orphan*/  git_worktree_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_worktree_is_locked (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  is_worktree_dir (char const*) ; 

__attribute__((used)) static int open_worktree_dir(git_worktree **out, const char *parent, const char *dir, const char *name)
{
	git_buf gitdir = GIT_BUF_INIT;
	git_worktree *wt = NULL;
	int error = 0;

	if (!is_worktree_dir(dir)) {
		error = -1;
		goto out;
	}

	if ((wt = git__calloc(1, sizeof(*wt))) == NULL) {
		error = -1;
		goto out;
	}

	if ((wt->name = git__strdup(name)) == NULL
	    || (wt->commondir_path = git_worktree__read_link(dir, "commondir")) == NULL
	    || (wt->gitlink_path = git_worktree__read_link(dir, "gitdir")) == NULL
	    || (parent && (wt->parent_path = git__strdup(parent)) == NULL)
	    || (wt->worktree_path = git_path_dirname(wt->gitlink_path)) == NULL) {
		error = -1;
		goto out;
	}

	if ((error = git_path_prettify_dir(&gitdir, dir, NULL)) < 0)
		goto out;
	wt->gitdir_path = git_buf_detach(&gitdir);

	wt->locked = !!git_worktree_is_locked(NULL, wt);

	*out = wt;

out:
	if (error)
		git_worktree_free(wt);
	git_buf_dispose(&gitdir);

	return error;
}