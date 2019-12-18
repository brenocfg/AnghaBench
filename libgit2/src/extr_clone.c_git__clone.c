#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int (* git_repository_create_cb ) (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_error_state ;
struct TYPE_12__ {int (* repository_cb ) (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ local; int /*<<< orphan*/  checkout_branch; int /*<<< orphan*/  checkout_opts; int /*<<< orphan*/  fetch_opts; int /*<<< orphan*/  repository_cb_payload; int /*<<< orphan*/  bare; } ;
typedef  TYPE_2__ git_clone_options ;

/* Variables and functions */
 scalar_t__ GIT_CLONE_LOCAL_NO_LINKS ; 
 TYPE_2__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CLONE_OPTIONS_VERSION ; 
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  GIT_RMDIR_SKIP_ROOT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int clone_into (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int clone_local_into (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int create_and_configure_origin (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_2__*) ; 
 int default_repository_create (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_clone__should_clone_local (char const*,scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_error_state_capture (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_error_state_restore (TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_exists (char const*) ; 
 int /*<<< orphan*/  git_path_is_empty_dir (char const*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static int git__clone(
	git_repository **out,
	const char *url,
	const char *local_path,
	const git_clone_options *_options,
	int use_existing)
{
	int error = 0;
	git_repository *repo = NULL;
	git_remote *origin;
	git_clone_options options = GIT_CLONE_OPTIONS_INIT;
	uint32_t rmdir_flags = GIT_RMDIR_REMOVE_FILES;
	git_repository_create_cb repository_cb;

	assert(out && url && local_path);

	if (_options)
		memcpy(&options, _options, sizeof(git_clone_options));

	GIT_ERROR_CHECK_VERSION(&options, GIT_CLONE_OPTIONS_VERSION, "git_clone_options");

	/* Only clone to a new directory or an empty directory */
	if (git_path_exists(local_path) && !use_existing && !git_path_is_empty_dir(local_path)) {
		git_error_set(GIT_ERROR_INVALID,
			"'%s' exists and is not an empty directory", local_path);
		return GIT_EEXISTS;
	}

	/* Only remove the root directory on failure if we create it */
	if (git_path_exists(local_path))
		rmdir_flags |= GIT_RMDIR_SKIP_ROOT;

	if (options.repository_cb)
		repository_cb = options.repository_cb;
	else
		repository_cb = default_repository_create;

	if ((error = repository_cb(&repo, local_path, options.bare, options.repository_cb_payload)) < 0)
		return error;

	if (!(error = create_and_configure_origin(&origin, repo, url, &options))) {
		int clone_local = git_clone__should_clone_local(url, options.local);
		int link = options.local != GIT_CLONE_LOCAL_NO_LINKS;

		if (clone_local == 1)
			error = clone_local_into(
				repo, origin, &options.fetch_opts, &options.checkout_opts,
				options.checkout_branch, link);
		else if (clone_local == 0)
			error = clone_into(
				repo, origin, &options.fetch_opts, &options.checkout_opts,
				options.checkout_branch);
		else
			error = -1;

		git_remote_free(origin);
	}

	if (error != 0) {
		git_error_state last_error = {0};
		git_error_state_capture(&last_error, error);

		git_repository_free(repo);
		repo = NULL;

		(void)git_futils_rmdir_r(local_path, NULL, rmdir_flags);

		git_error_state_restore(&last_error);
	}

	*out = repo;
	return error;
}