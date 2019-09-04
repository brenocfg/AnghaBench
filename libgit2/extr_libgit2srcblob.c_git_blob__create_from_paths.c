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
struct stat {scalar_t__ st_mode; scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  st ;
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  scalar_t__ git_off_t ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_filter_list ;
struct TYPE_5__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_EBAREREPO ; 
 int GIT_EDIRECTORY ; 
 int /*<<< orphan*/  GIT_ERROR_ODB ; 
 int /*<<< orphan*/  GIT_FILTER_DEFAULT ; 
 int /*<<< orphan*/  GIT_FILTER_TO_ODB ; 
 scalar_t__ S_ISDIR (scalar_t__) ; 
 scalar_t__ S_ISLNK (scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int git_filter_list_load (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int git_path_lstat (char const*,struct stat*) ; 
 scalar_t__ git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 int git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct stat*,struct stat*,int) ; 
 int write_file_filtered (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int write_file_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int write_symlink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t) ; 

int git_blob__create_from_paths(
	git_oid *id,
	struct stat *out_st,
	git_repository *repo,
	const char *content_path,
	const char *hint_path,
	mode_t hint_mode,
	bool try_load_filters)
{
	int error;
	struct stat st;
	git_odb *odb = NULL;
	git_off_t size;
	mode_t mode;
	git_buf path = GIT_BUF_INIT;

	assert(hint_path || !try_load_filters);

	if (!content_path) {
		if (git_repository__ensure_not_bare(repo, "create blob from file") < 0)
			return GIT_EBAREREPO;

		if (git_buf_joinpath(
				&path, git_repository_workdir(repo), hint_path) < 0)
			return -1;

		content_path = path.ptr;
	}

	if ((error = git_path_lstat(content_path, &st)) < 0 ||
		(error = git_repository_odb(&odb, repo)) < 0)
		goto done;

	if (S_ISDIR(st.st_mode)) {
		git_error_set(GIT_ERROR_ODB, "cannot create blob from '%s': it is a directory", content_path);
		error = GIT_EDIRECTORY;
		goto done;
	}

	if (out_st)
		memcpy(out_st, &st, sizeof(st));

	size = st.st_size;
	mode = hint_mode ? hint_mode : st.st_mode;

	if (S_ISLNK(mode)) {
		error = write_symlink(id, odb, content_path, (size_t)size);
	} else {
		git_filter_list *fl = NULL;

		if (try_load_filters)
			/* Load the filters for writing this file to the ODB */
			error = git_filter_list_load(
				&fl, repo, NULL, hint_path,
				GIT_FILTER_TO_ODB, GIT_FILTER_DEFAULT);

		if (error < 0)
			/* well, that didn't work */;
		else if (fl == NULL)
			/* No filters need to be applied to the document: we can stream
			 * directly from disk */
			error = write_file_stream(id, odb, content_path, size);
		else {
			/* We need to apply one or more filters */
			error = write_file_filtered(id, &size, odb, content_path, fl);

			git_filter_list_free(fl);
		}

		/*
		 * TODO: eventually support streaming filtered files, for files
		 * which are bigger than a given threshold. This is not a priority
		 * because applying a filter in streaming mode changes the final
		 * size of the blob, and without knowing its final size, the blob
		 * cannot be written in stream mode to the ODB.
		 *
		 * The plan is to do streaming writes to a tempfile on disk and then
		 * opening streaming that file to the ODB, using
		 * `write_file_stream`.
		 *
		 * CAREFULLY DESIGNED APIS YO
		 */
	}

done:
	git_odb_free(odb);
	git_buf_dispose(&path);

	return error;
}