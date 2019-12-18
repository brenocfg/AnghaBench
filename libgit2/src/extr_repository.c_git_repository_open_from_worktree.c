#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gitlink_path; } ;
typedef  TYPE_1__ git_worktree ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_set (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

int git_repository_open_from_worktree(git_repository **repo_out, git_worktree *wt)
{
	git_buf path = GIT_BUF_INIT;
	git_repository *repo = NULL;
	size_t len;
	int err;

	assert(repo_out && wt);

	*repo_out = NULL;
	len = strlen(wt->gitlink_path);

	if (len <= 4 || strcasecmp(wt->gitlink_path + len - 4, ".git")) {
		err = -1;
		goto out;
	}

	if ((err = git_buf_set(&path, wt->gitlink_path, len - 4)) < 0)
		goto out;

	if ((err = git_repository_open(&repo, path.ptr)) < 0)
		goto out;

	*repo_out = repo;

out:
	git_buf_dispose(&path);

	return err;
}