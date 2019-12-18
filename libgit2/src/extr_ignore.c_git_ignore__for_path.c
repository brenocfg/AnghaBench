#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_20__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_17__ {int /*<<< orphan*/  ign_global; TYPE_7__ dir; int /*<<< orphan*/  ign_internal; int /*<<< orphan*/  dir_root; int /*<<< orphan*/  ignore_case; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ git_ignores ;
struct TYPE_18__ {char* ptr; } ;
typedef  TYPE_2__ git_buf ;
struct TYPE_19__ {int /*<<< orphan*/ * cfg_excl_file; } ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_IGNORECASE ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/ * GIT_IGNORE_FILE_INREPO ; 
 int /*<<< orphan*/  GIT_REPOSITORY_ITEM_INFO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int get_internal_ignores (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__prefixcmp (int /*<<< orphan*/ ,char const*) ; 
 int git_attr_cache__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_joinpath (TYPE_7__*,char const*,char*) ; 
 int /*<<< orphan*/  git_ignore__free (TYPE_1__*) ; 
 int git_path_dirname_r (TYPE_2__*,char const*) ; 
 int git_path_resolve_relative (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_root (char const*) ; 
 int git_path_to_dir (TYPE_2__*) ; 
 int git_path_walk_up (TYPE_7__*,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int git_repository__configmap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* git_repository_attr_cache (int /*<<< orphan*/ *) ; 
 int git_repository_item_path (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int push_ignore_file (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_one_ignore ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_ignore__for_path(
	git_repository *repo,
	const char *path,
	git_ignores *ignores)
{
	int error = 0;
	const char *workdir = git_repository_workdir(repo);
	git_buf infopath = GIT_BUF_INIT;

	assert(repo && ignores && path);

	memset(ignores, 0, sizeof(*ignores));
	ignores->repo = repo;

	/* Read the ignore_case flag */
	if ((error = git_repository__configmap_lookup(
			&ignores->ignore_case, repo, GIT_CONFIGMAP_IGNORECASE)) < 0)
		goto cleanup;

	if ((error = git_attr_cache__init(repo)) < 0)
		goto cleanup;

	/* given a unrooted path in a non-bare repo, resolve it */
	if (workdir && git_path_root(path) < 0) {
		git_buf local = GIT_BUF_INIT;

		if ((error = git_path_dirname_r(&local, path)) < 0 ||
		    (error = git_path_resolve_relative(&local, 0)) < 0 ||
		    (error = git_path_to_dir(&local)) < 0 ||
		    (error = git_buf_joinpath(&ignores->dir, workdir, local.ptr)) < 0)
		{;} /* Nothing, we just want to stop on the first error */
		git_buf_dispose(&local);
	} else {
		error = git_buf_joinpath(&ignores->dir, path, "");
	}
	if (error < 0)
		goto cleanup;

	if (workdir && !git__prefixcmp(ignores->dir.ptr, workdir))
		ignores->dir_root = strlen(workdir);

	/* set up internals */
	if ((error = get_internal_ignores(&ignores->ign_internal, repo)) < 0)
		goto cleanup;

	/* load .gitignore up the path */
	if (workdir != NULL) {
		error = git_path_walk_up(
			&ignores->dir, workdir, push_one_ignore, ignores);
		if (error < 0)
			goto cleanup;
	}

	/* load .git/info/exclude if possible */
	if ((error = git_repository_item_path(&infopath, repo, GIT_REPOSITORY_ITEM_INFO)) < 0 ||
		(error = push_ignore_file(ignores, &ignores->ign_global, infopath.ptr, GIT_IGNORE_FILE_INREPO)) < 0) {
		if (error != GIT_ENOTFOUND)
			goto cleanup;
		error = 0;
	}

	/* load core.excludesfile */
	if (git_repository_attr_cache(repo)->cfg_excl_file != NULL)
		error = push_ignore_file(
			ignores, &ignores->ign_global, NULL,
			git_repository_attr_cache(repo)->cfg_excl_file);

cleanup:
	git_buf_dispose(&infopath);
	if (error < 0)
		git_ignore__free(ignores);

	return error;
}