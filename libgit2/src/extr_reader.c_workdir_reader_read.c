#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ index; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ workdir_reader ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  git_reader ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_11__ {scalar_t__ mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_filter_list ;
typedef  scalar_t__ git_filemode_t ;
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 TYPE_3__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_FILTER_DEFAULT ; 
 int /*<<< orphan*/  GIT_FILTER_TO_ODB ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int GIT_READER_MISMATCH ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int git_buf_joinpath (TYPE_3__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int git_filter_list_apply_to_file (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int git_filter_list_load (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_futils_canonical_mode (int /*<<< orphan*/ ) ; 
 TYPE_2__* git_index_get_bypath (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int git_odb_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int p_lstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int workdir_reader_read(
	git_buf *out,
	git_oid *out_id,
	git_filemode_t *out_filemode,
	git_reader *_reader,
	const char *filename)
{
	workdir_reader *reader = (workdir_reader *)_reader;
	git_buf path = GIT_BUF_INIT;
	struct stat st;
	git_filemode_t filemode;
	git_filter_list *filters = NULL;
	const git_index_entry *idx_entry;
	git_oid id;
	int error;

	if ((error = git_buf_joinpath(&path,
		git_repository_workdir(reader->repo), filename)) < 0)
		goto done;

	if ((error = p_lstat(path.ptr, &st)) < 0) {
		if (error == -1 && errno == ENOENT)
			error = GIT_ENOTFOUND;

		git_error_set(GIT_ERROR_OS, "could not stat '%s'", path.ptr);
		goto done;
	}

	filemode = git_futils_canonical_mode(st.st_mode);

	/*
	 * Patch application - for example - uses the filtered version of
	 * the working directory data to match git.  So we will run the
	 * workdir -> ODB filter on the contents in this workdir reader.
	 */
	if ((error = git_filter_list_load(&filters, reader->repo, NULL, filename,
		GIT_FILTER_TO_ODB, GIT_FILTER_DEFAULT)) < 0)
		goto done;

	if ((error = git_filter_list_apply_to_file(out,
	    filters, reader->repo, path.ptr)) < 0)
		goto done;

	if (out_id || reader->index) {
		if ((error = git_odb_hash(&id, out->ptr, out->size, GIT_OBJECT_BLOB)) < 0)
			goto done;
	}

	if (reader->index) {
		if (!(idx_entry = git_index_get_bypath(reader->index, filename, 0)) ||
		    filemode != idx_entry->mode ||
		    !git_oid_equal(&id, &idx_entry->id)) {
			error = GIT_READER_MISMATCH;
			goto done;
		}
	}

	if (out_id)
		git_oid_cpy(out_id, &id);

	if (out_filemode)
		*out_filemode = filemode;

done:
	git_filter_list_free(filters);
	git_buf_dispose(&path);
	return error;
}