#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int flags; char* fetchspec; int /*<<< orphan*/ * name; int /*<<< orphan*/  repository; } ;
typedef  TYPE_1__ git_remote_create_options ;
struct TYPE_21__ {int /*<<< orphan*/  download_tags; int /*<<< orphan*/  refs; int /*<<< orphan*/  refspecs; int /*<<< orphan*/  active_refspecs; struct TYPE_21__* name; struct TYPE_21__* url; int /*<<< orphan*/  repo; } ;
typedef  TYPE_2__ git_remote ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_22__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_URL_FMT ; 
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_1__ const*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ GIT_REMOTE_CREATE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_CREATE_OPTIONS_VERSION ; 
 int GIT_REMOTE_CREATE_SKIP_DEFAULT_FETCHSPEC ; 
 int GIT_REMOTE_CREATE_SKIP_INSTEADOF ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_AUTO ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_NONE ; 
 int add_refspec (TYPE_2__*,char const*,int) ; 
 TYPE_2__* apply_insteadof (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int canonicalize_url (TYPE_3__*,char const*) ; 
 int default_fetchspec_for_name (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int dwim_refspecs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ensure_remote_doesnot_exist (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ensure_remote_name_is_valid (int /*<<< orphan*/ *) ; 
 TYPE_2__* git__calloc (int,int) ; 
 void* git__strdup (int /*<<< orphan*/ *) ; 
 char* git_buf_cstr (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int git_buf_printf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (TYPE_2__*) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int lookup_remote_prune_config (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int write_add_refspec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int) ; 

int git_remote_create_with_opts(git_remote **out, const char *url, const git_remote_create_options *opts)
{
	git_remote *remote = NULL;
	git_config *config_ro = NULL, *config_rw;
	git_buf canonical_url = GIT_BUF_INIT;
	git_buf var = GIT_BUF_INIT;
	git_buf specbuf = GIT_BUF_INIT;
	const git_remote_create_options dummy_opts = GIT_REMOTE_CREATE_OPTIONS_INIT;
	int error = -1;

	assert(out && url);

	if (!opts) {
		opts = &dummy_opts;
	}

	GIT_ERROR_CHECK_VERSION(opts, GIT_REMOTE_CREATE_OPTIONS_VERSION, "git_remote_create_options");

	if (opts->name != NULL) {
		if ((error = ensure_remote_name_is_valid(opts->name)) < 0)
			return error;

		if (opts->repository &&
		    (error = ensure_remote_doesnot_exist(opts->repository, opts->name)) < 0)
			return error;
	}

	if (opts->repository) {
		if ((error = git_repository_config_snapshot(&config_ro, opts->repository)) < 0)
			goto on_error;
	}

	remote = git__calloc(1, sizeof(git_remote));
	GIT_ERROR_CHECK_ALLOC(remote);

	remote->repo = opts->repository;

	if ((error = git_vector_init(&remote->refs, 8, NULL)) < 0 ||
		(error = canonicalize_url(&canonical_url, url)) < 0)
		goto on_error;

	if (opts->repository && !(opts->flags & GIT_REMOTE_CREATE_SKIP_INSTEADOF)) {
		remote->url = apply_insteadof(config_ro, canonical_url.ptr, GIT_DIRECTION_FETCH);
	} else {
		remote->url = git__strdup(canonical_url.ptr);
	}
	GIT_ERROR_CHECK_ALLOC(remote->url);

	if (opts->name != NULL) {
		remote->name = git__strdup(opts->name);
		GIT_ERROR_CHECK_ALLOC(remote->name);

		if (opts->repository &&
		    ((error = git_buf_printf(&var, CONFIG_URL_FMT, opts->name)) < 0 ||
		    (error = git_repository_config__weakptr(&config_rw, opts->repository)) < 0 ||
		    (error = git_config_set_string(config_rw, var.ptr, canonical_url.ptr)) < 0))
			goto on_error;
	}

	if (opts->fetchspec != NULL ||
	    (opts->name && !(opts->flags & GIT_REMOTE_CREATE_SKIP_DEFAULT_FETCHSPEC))) {
		const char *fetch = NULL;
		if (opts->fetchspec) {
			fetch = opts->fetchspec;
		} else {
			if ((error = default_fetchspec_for_name(&specbuf, opts->name)) < 0)
				goto on_error;

			fetch = git_buf_cstr(&specbuf);
		}

		if ((error = add_refspec(remote, fetch, true)) < 0)
			goto on_error;

		/* only write for named remotes with a repository */
		if (opts->repository && opts->name &&
		    ((error = write_add_refspec(opts->repository, opts->name, fetch, true)) < 0 ||
		    (error = lookup_remote_prune_config(remote, config_ro, opts->name)) < 0))
			goto on_error;

		/* Move the data over to where the matching functions can find them */
		if ((error = dwim_refspecs(&remote->active_refspecs, &remote->refspecs, &remote->refs)) < 0)
			goto on_error;
	}

	/* A remote without a name doesn't download tags */
	if (!opts->name)
		remote->download_tags = GIT_REMOTE_DOWNLOAD_TAGS_NONE;
	else
		remote->download_tags = GIT_REMOTE_DOWNLOAD_TAGS_AUTO;


	git_buf_dispose(&var);

	*out = remote;
	error = 0;

on_error:
	if (error)
		git_remote_free(remote);

	git_config_free(config_ro);
	git_buf_dispose(&specbuf);
	git_buf_dispose(&canonical_url);
	git_buf_dispose(&var);
	return error;
}