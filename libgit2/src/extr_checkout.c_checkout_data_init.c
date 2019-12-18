#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_22__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_23__ {int /*<<< orphan*/  target_directory; } ;
typedef  TYPE_2__ git_checkout_options ;
struct TYPE_25__ {int checkout_strategy; int file_open_flags; int /*<<< orphan*/  target_directory; int /*<<< orphan*/  baseline; int /*<<< orphan*/  baseline_index; int /*<<< orphan*/  paths; scalar_t__ dir_mode; } ;
struct TYPE_24__ {int strategy; int opts_free_baseline; int /*<<< orphan*/ * repo; int /*<<< orphan*/  attr_session; int /*<<< orphan*/  target_path; int /*<<< orphan*/  target_len; int /*<<< orphan*/  mkdir_map; TYPE_5__ opts; int /*<<< orphan*/  update_conflicts; int /*<<< orphan*/  remove_conflicts; int /*<<< orphan*/  removes; int /*<<< orphan*/  pool; TYPE_7__* index; int /*<<< orphan*/  respect_filemode; int /*<<< orphan*/  can_symlink; int /*<<< orphan*/  pfx; int /*<<< orphan*/ * target; } ;
typedef  TYPE_3__ checkout_data ;
struct TYPE_26__ {scalar_t__ on_disk; } ;

/* Variables and functions */
 int GIT_CHECKOUT_CONFLICT_STYLE_DIFF3 ; 
 int GIT_CHECKOUT_CONFLICT_STYLE_MERGE ; 
 int GIT_CHECKOUT_FORCE ; 
 int GIT_CHECKOUT_NO_REFRESH ; 
 int /*<<< orphan*/  GIT_CHECKOUT_OPTIONS_VERSION ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_FILEMODE ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_SYMLINKS ; 
 scalar_t__ GIT_DIR_MODE ; 
 int GIT_ECONFLICT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECKOUT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_2__ const*,int /*<<< orphan*/ ,char*) ; 
 int GIT_EUNBORNBRANCH ; 
 int /*<<< orphan*/  GIT_INIT_STRUCTURE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_MKDIR_VERIFY_DIR ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  checkout_data_clear (TYPE_3__*) ; 
 int checkout_lookup_head_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int checkout_mkdir (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git__strcmp_cb ; 
 int /*<<< orphan*/  git_attr_session__init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 int git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int git_config_get_entry (TYPE_1__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ git_index_has_conflicts (TYPE_7__*) ; 
 int /*<<< orphan*/  git_index_name_clear (TYPE_7__*) ; 
 int git_index_read (TYPE_7__*,int) ; 
 int git_index_read_safely (TYPE_7__*) ; 
 int /*<<< orphan*/  git_index_reuc_clear (TYPE_7__*) ; 
 TYPE_7__* git_iterator_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_iterator_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_isdir (int /*<<< orphan*/ ) ; 
 int git_path_to_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 int git_repository__configmap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_repository_index (TYPE_7__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int git_strmap_new (int /*<<< orphan*/ *) ; 
 int git_vector_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (TYPE_5__*,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int checkout_data_init(
	checkout_data *data,
	git_iterator *target,
	const git_checkout_options *proposed)
{
	int error = 0;
	git_repository *repo = git_iterator_owner(target);

	memset(data, 0, sizeof(*data));

	if (!repo) {
		git_error_set(GIT_ERROR_CHECKOUT, "cannot checkout nothing");
		return -1;
	}

	if ((!proposed || !proposed->target_directory) &&
		(error = git_repository__ensure_not_bare(repo, "checkout")) < 0)
		return error;

	data->repo = repo;
	data->target = target;

	GIT_ERROR_CHECK_VERSION(
		proposed, GIT_CHECKOUT_OPTIONS_VERSION, "git_checkout_options");

	if (!proposed)
		GIT_INIT_STRUCTURE(&data->opts, GIT_CHECKOUT_OPTIONS_VERSION);
	else
		memmove(&data->opts, proposed, sizeof(git_checkout_options));

	if (!data->opts.target_directory)
		data->opts.target_directory = git_repository_workdir(repo);
	else if (!git_path_isdir(data->opts.target_directory) &&
			 (error = checkout_mkdir(data,
				data->opts.target_directory, NULL,
				GIT_DIR_MODE, GIT_MKDIR_VERIFY_DIR)) < 0)
		goto cleanup;

	if ((error = git_repository_index(&data->index, data->repo)) < 0)
		goto cleanup;

	/* refresh config and index content unless NO_REFRESH is given */
	if ((data->opts.checkout_strategy & GIT_CHECKOUT_NO_REFRESH) == 0) {
		git_config *cfg;

		if ((error = git_repository_config__weakptr(&cfg, repo)) < 0)
			goto cleanup;

		/* Reload the repository index (unless we're checking out the
		 * index; then it has the changes we're trying to check out
		 * and those should not be overwritten.)
		 */
		if (data->index != git_iterator_index(target)) {
			if (data->opts.checkout_strategy & GIT_CHECKOUT_FORCE) {
				/* When forcing, we can blindly re-read the index */
				if ((error = git_index_read(data->index, false)) < 0)
					goto cleanup;
			} else {
				/*
				 * When not being forced, we need to check for unresolved
				 * conflicts and unsaved changes in the index before
				 * proceeding.
				 */
				if (git_index_has_conflicts(data->index)) {
					error = GIT_ECONFLICT;
					git_error_set(GIT_ERROR_CHECKOUT,
						"unresolved conflicts exist in the index");
					goto cleanup;
				}

				if ((error = git_index_read_safely(data->index)) < 0)
					goto cleanup;
			}

			/* clean conflict data in the current index */
			git_index_name_clear(data->index);
			git_index_reuc_clear(data->index);
		}
	}

	/* if you are forcing, allow all safe updates, plus recreate missing */
	if ((data->opts.checkout_strategy & GIT_CHECKOUT_FORCE) != 0)
		data->opts.checkout_strategy |= GIT_CHECKOUT_SAFE |
			GIT_CHECKOUT_RECREATE_MISSING;

	/* if the repository does not actually have an index file, then this
	 * is an initial checkout (perhaps from clone), so we allow safe updates
	 */
	if (!data->index->on_disk &&
		(data->opts.checkout_strategy & GIT_CHECKOUT_SAFE) != 0)
		data->opts.checkout_strategy |= GIT_CHECKOUT_RECREATE_MISSING;

	data->strategy = data->opts.checkout_strategy;

	/* opts->disable_filters is false by default */

	if (!data->opts.dir_mode)
		data->opts.dir_mode = GIT_DIR_MODE;

	if (!data->opts.file_open_flags)
		data->opts.file_open_flags = O_CREAT | O_TRUNC | O_WRONLY;

	data->pfx = git_pathspec_prefix(&data->opts.paths);

	if ((error = git_repository__configmap_lookup(
			 &data->can_symlink, repo, GIT_CONFIGMAP_SYMLINKS)) < 0)
		goto cleanup;

	if ((error = git_repository__configmap_lookup(
			 &data->respect_filemode, repo, GIT_CONFIGMAP_FILEMODE)) < 0)
		goto cleanup;

	if (!data->opts.baseline && !data->opts.baseline_index) {
		data->opts_free_baseline = true;
		error = 0;

		/* if we don't have an index, this is an initial checkout and
		 * should be against an empty baseline
		 */
		if (data->index->on_disk)
			error = checkout_lookup_head_tree(&data->opts.baseline, repo);

		if (error == GIT_EUNBORNBRANCH) {
			error = 0;
			git_error_clear();
		}

		if (error < 0)
			goto cleanup;
	}

	if ((data->opts.checkout_strategy &
		(GIT_CHECKOUT_CONFLICT_STYLE_MERGE | GIT_CHECKOUT_CONFLICT_STYLE_DIFF3)) == 0) {
		git_config_entry *conflict_style = NULL;
		git_config *cfg = NULL;

		if ((error = git_repository_config__weakptr(&cfg, repo)) < 0 ||
			(error = git_config_get_entry(&conflict_style, cfg, "merge.conflictstyle")) < 0 ||
			error == GIT_ENOTFOUND)
			;
		else if (error)
			goto cleanup;
		else if (strcmp(conflict_style->value, "merge") == 0)
			data->opts.checkout_strategy |= GIT_CHECKOUT_CONFLICT_STYLE_MERGE;
		else if (strcmp(conflict_style->value, "diff3") == 0)
			data->opts.checkout_strategy |= GIT_CHECKOUT_CONFLICT_STYLE_DIFF3;
		else {
			git_error_set(GIT_ERROR_CHECKOUT, "unknown style '%s' given for 'merge.conflictstyle'",
				conflict_style->value);
			error = -1;
			git_config_entry_free(conflict_style);
			goto cleanup;
		}
		git_config_entry_free(conflict_style);
	}

	git_pool_init(&data->pool, 1);

	if ((error = git_vector_init(&data->removes, 0, git__strcmp_cb)) < 0 ||
	    (error = git_vector_init(&data->remove_conflicts, 0, NULL)) < 0 ||
	    (error = git_vector_init(&data->update_conflicts, 0, NULL)) < 0 ||
	    (error = git_buf_puts(&data->target_path, data->opts.target_directory)) < 0 ||
	    (error = git_path_to_dir(&data->target_path)) < 0 ||
	    (error = git_strmap_new(&data->mkdir_map)) < 0)
		goto cleanup;

	data->target_len = git_buf_len(&data->target_path);

	git_attr_session__init(&data->attr_session, data->repo);

cleanup:
	if (error < 0)
		checkout_data_clear(data);

	return error;
}