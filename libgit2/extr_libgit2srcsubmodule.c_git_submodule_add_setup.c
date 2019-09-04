#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  DOT_GIT ; 
 int /*<<< orphan*/  GITMODULES_CREATE ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int git_buf_printf (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_config_backend_free (int /*<<< orphan*/ *) ; 
 int git_config_backend_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ git_path_contains (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_root (char const*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int git_submodule_init (int /*<<< orphan*/ *,int) ; 
 int git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int git_submodule_resolve_url (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int is_path_occupied (int*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * open_gitmodules (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int submodule_config_key_trunc_puts (TYPE_1__*,char*) ; 
 int submodule_repo_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 

int git_submodule_add_setup(
	git_submodule **out,
	git_repository *repo,
	const char *url,
	const char *path,
	int use_gitlink)
{
	int error = 0;
	git_config_backend *mods = NULL;
	git_submodule *sm = NULL;
	git_buf name = GIT_BUF_INIT, real_url = GIT_BUF_INIT;
	git_repository *subrepo = NULL;
	bool path_occupied;

	assert(repo && url && path);

	/* see if there is already an entry for this submodule */

	if (git_submodule_lookup(NULL, repo, path) < 0)
		git_error_clear();
	else {
		git_error_set(GIT_ERROR_SUBMODULE,
			"attempt to add submodule '%s' that already exists", path);
		return GIT_EEXISTS;
	}

	/* validate and normalize path */

	if (git__prefixcmp(path, git_repository_workdir(repo)) == 0)
		path += strlen(git_repository_workdir(repo));

	if (git_path_root(path) >= 0) {
		git_error_set(GIT_ERROR_SUBMODULE, "submodule path must be a relative path");
		error = -1;
		goto cleanup;
	}

	if ((error = is_path_occupied(&path_occupied, repo, path)) < 0)
		goto cleanup;

	if (path_occupied) {
		error = GIT_EEXISTS;
		goto cleanup;
	}

	/* update .gitmodules */

	if (!(mods = open_gitmodules(repo, GITMODULES_CREATE))) {
		git_error_set(GIT_ERROR_SUBMODULE,
			"adding submodules to a bare repository is not supported");
		return -1;
	}

	if ((error = git_buf_printf(&name, "submodule.%s.path", path)) < 0 ||
		(error = git_config_backend_set_string(mods, name.ptr, path)) < 0)
		goto cleanup;

	if ((error = submodule_config_key_trunc_puts(&name, "url")) < 0 ||
		(error = git_config_backend_set_string(mods, name.ptr, url)) < 0)
		goto cleanup;

	git_buf_clear(&name);

	/* init submodule repository and add origin remote as needed */

	error = git_buf_joinpath(&name, git_repository_workdir(repo), path);
	if (error < 0)
		goto cleanup;

	/* if the repo does not already exist, then init a new repo and add it.
	 * Otherwise, just add the existing repo.
	 */
	if (!(git_path_exists(name.ptr) &&
		git_path_contains(&name, DOT_GIT))) {

		/* resolve the actual URL to use */
		if ((error = git_submodule_resolve_url(&real_url, repo, url)) < 0)
			goto cleanup;

		 if ((error = submodule_repo_init(&subrepo, repo, path, real_url.ptr, use_gitlink)) < 0)
			goto cleanup;
	}

	if ((error = git_submodule_lookup(&sm, repo, path)) < 0)
		goto cleanup;

	error = git_submodule_init(sm, false);

cleanup:
	if (error && sm) {
		git_submodule_free(sm);
		sm = NULL;
	}
	if (out != NULL)
		*out = sm;

	git_config_backend_free(mods);
	git_repository_free(subrepo);
	git_buf_dispose(&real_url);
	git_buf_dispose(&name);

	return error;
}