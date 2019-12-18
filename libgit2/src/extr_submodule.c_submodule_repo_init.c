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
struct TYPE_9__ {int flags; char const* origin_url; int /*<<< orphan*/  workdir_path; } ;
typedef  TYPE_1__ git_repository_init_options ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_REPOSITORY_INIT_MKPATH ; 
 int GIT_REPOSITORY_INIT_NO_DOTGIT_DIR ; 
 int GIT_REPOSITORY_INIT_NO_REINIT ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int GIT_REPOSITORY_INIT_RELATIVE_GITLINK ; 
 int /*<<< orphan*/  GIT_REPOSITORY_ITEM_MODULES ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int git_repository_init_ext (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int git_repository_item_path (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int submodule_repo_init(
	git_repository **out,
	git_repository *parent_repo,
	const char *path,
	const char *url,
	bool use_gitlink)
{
	int error = 0;
	git_buf workdir = GIT_BUF_INIT, repodir = GIT_BUF_INIT;
	git_repository_init_options initopt = GIT_REPOSITORY_INIT_OPTIONS_INIT;
	git_repository *subrepo = NULL;

	error = git_buf_joinpath(&workdir, git_repository_workdir(parent_repo), path);
	if (error < 0)
		goto cleanup;

	initopt.flags = GIT_REPOSITORY_INIT_MKPATH | GIT_REPOSITORY_INIT_NO_REINIT;
	initopt.origin_url = url;

	/* init submodule repository and add origin remote as needed */

	/* New style: sub-repo goes in <repo-dir>/modules/<name>/ with a
	 * gitlink in the sub-repo workdir directory to that repository
	 *
	 * Old style: sub-repo goes directly into repo/<name>/.git/
	 */
	 if (use_gitlink) {
		error = git_repository_item_path(&repodir, parent_repo, GIT_REPOSITORY_ITEM_MODULES);
		if (error < 0)
			goto cleanup;
		error = git_buf_joinpath(&repodir, repodir.ptr, path);
		if (error < 0)
			goto cleanup;

		initopt.workdir_path = workdir.ptr;
		initopt.flags |=
			GIT_REPOSITORY_INIT_NO_DOTGIT_DIR |
			GIT_REPOSITORY_INIT_RELATIVE_GITLINK;

		error = git_repository_init_ext(&subrepo, repodir.ptr, &initopt);
	} else
		error = git_repository_init_ext(&subrepo, workdir.ptr, &initopt);

cleanup:
	git_buf_dispose(&workdir);
	git_buf_dispose(&repodir);

	*out = subrepo;

	return error;
}