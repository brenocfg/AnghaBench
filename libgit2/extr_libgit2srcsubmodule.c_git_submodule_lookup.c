#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  path; scalar_t__ name; } ;
typedef  TYPE_1__ git_submodule ;
struct TYPE_23__ {int /*<<< orphan*/ * submodule_cache; scalar_t__ is_bare; } ;
typedef  TYPE_2__ git_repository ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_24__ {char* ptr; int size; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_25__ {char* path; scalar_t__ name; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_4__ fbp_data ;

/* Variables and functions */
 int /*<<< orphan*/  DOT_GIT ; 
 int /*<<< orphan*/  GITMODULES_EXISTING ; 
 TYPE_3__ GIT_BUF_INIT ; 
 int GIT_EEXISTS ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 unsigned int GIT_SUBMODULE_STATUS_IN_WD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  find_by_path ; 
 int /*<<< orphan*/  git__free (scalar_t__) ; 
 int /*<<< orphan*/  git_buf_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 scalar_t__ git_buf_join3 (TYPE_3__*,char,scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_3__*,char const*) ; 
 int git_config_backend_foreach_match (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  git_config_backend_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_path_exists (char*) ; 
 scalar_t__ git_repository_workdir (TYPE_2__*) ; 
 TYPE_1__* git_strmap_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_submodule_free (TYPE_1__*) ; 
 int git_submodule_location (unsigned int*,TYPE_1__*) ; 
 int git_submodule_reload (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * open_gitmodules (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int submodule_alloc (TYPE_1__**,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  submodule_set_lookup_error (int,char const*) ; 

int git_submodule_lookup(
	git_submodule **out, /* NULL if user only wants to test existence */
	git_repository *repo,
	const char *name)    /* trailing slash is allowed */
{
	int error;
	unsigned int location;
	git_submodule *sm;

	assert(repo && name);

	if (repo->is_bare) {
		git_error_set(GIT_ERROR_SUBMODULE, "cannot get submodules without a working tree");
		return -1;
	}

	if (repo->submodule_cache != NULL) {
		if ((sm = git_strmap_get(repo->submodule_cache, name)) != NULL) {
			if (out) {
				*out = sm;
				GIT_REFCOUNT_INC(*out);
			}
			return 0;
		}
	}

	if ((error = submodule_alloc(&sm, repo, name)) < 0)
		return error;

	if ((error = git_submodule_reload(sm, false)) < 0) {
		git_submodule_free(sm);
		return error;
	}

	if ((error = git_submodule_location(&location, sm)) < 0) {
		git_submodule_free(sm);
		return error;
	}

	/* If it's not configured or we're looking by path  */
	if (location == 0 || location == GIT_SUBMODULE_STATUS_IN_WD) {
		git_config_backend *mods;
		const char *pattern = "submodule\\..*\\.path";
		git_buf path = GIT_BUF_INIT;
		fbp_data data = { NULL, NULL };

		git_buf_puts(&path, name);
		while (path.ptr[path.size-1] == '/') {
			path.ptr[--path.size] = '\0';
		}
		data.path = path.ptr;

		mods = open_gitmodules(repo, GITMODULES_EXISTING);

		if (mods)
			error = git_config_backend_foreach_match(mods, pattern, find_by_path, &data);

		git_config_backend_free(mods);

		if (error < 0) {
			git_submodule_free(sm);
			git_buf_dispose(&path);
			return error;
		}

		if (data.name) {
			git__free(sm->name);
			sm->name = data.name;
			sm->path = git_buf_detach(&path);

			/* Try to load again with the right name */
			if ((error = git_submodule_reload(sm, false)) < 0) {
				git_submodule_free(sm);
				return error;
			}
		}

		git_buf_dispose(&path);
	}

	if ((error = git_submodule_location(&location, sm)) < 0) {
		git_submodule_free(sm);
		return error;
	}

	/* If we still haven't found it, do the WD check */
	if (location == 0 || location == GIT_SUBMODULE_STATUS_IN_WD) {
		git_submodule_free(sm);
		error = GIT_ENOTFOUND;

		/* If it's not configured, we still check if there's a repo at the path */
		if (git_repository_workdir(repo)) {
			git_buf path = GIT_BUF_INIT;
			if (git_buf_join3(&path,
					  '/', git_repository_workdir(repo), name, DOT_GIT) < 0)
				return -1;

			if (git_path_exists(path.ptr))
				error = GIT_EEXISTS;

			git_buf_dispose(&path);
		}

		submodule_set_lookup_error(error, name);
		return error;
	}

	if (out)
		*out = sm;
	else
		git_submodule_free(sm);

	return 0;
}