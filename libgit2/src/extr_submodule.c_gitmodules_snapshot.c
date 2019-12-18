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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_MODULES_FILE ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_joinpath (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gitmodules_snapshot(git_config **snap, git_repository *repo)
{
	const char *workdir = git_repository_workdir(repo);
	git_config *mods = NULL;
	git_buf path = GIT_BUF_INIT;
	int error;

	if (!workdir)
		return GIT_ENOTFOUND;

	if ((error = git_buf_joinpath(&path, workdir, GIT_MODULES_FILE)) < 0)
		return error;

	if ((error = git_config_open_ondisk(&mods, path.ptr)) < 0)
		goto cleanup;
	git_buf_dispose(&path);

	if ((error = git_config_snapshot(snap, mods)) < 0)
		goto cleanup;

	error = 0;

cleanup:
	if (mods)
		git_config_free(mods);
	git_buf_dispose(&path);

	return error;
}