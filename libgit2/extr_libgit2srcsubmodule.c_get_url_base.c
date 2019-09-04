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
struct TYPE_4__ {int /*<<< orphan*/  parent_path; } ;
typedef  TYPE_1__ git_worktree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int git_buf_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_is_worktree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_free (TYPE_1__*) ; 
 int git_worktree_open_from_repository (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int lookup_default_remote (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_url_base(git_buf *url, git_repository *repo)
{
	int error;
	git_worktree *wt = NULL;
	git_remote *remote = NULL;

	if ((error = lookup_default_remote(&remote, repo)) == 0) {
		error = git_buf_sets(url, git_remote_url(remote));
		goto out;
	} else if (error != GIT_ENOTFOUND)
		goto out;
	else
		git_error_clear();

	/* if repository does not have a default remote, use workdir instead */
	if (git_repository_is_worktree(repo)) {
		if ((error = git_worktree_open_from_repository(&wt, repo)) < 0)
			goto out;
		error = git_buf_sets(url, wt->parent_path);
	} else
		error = git_buf_sets(url, git_repository_workdir(repo));

out:
	git_remote_free(remote);
	git_worktree_free(wt);

	return error;
}