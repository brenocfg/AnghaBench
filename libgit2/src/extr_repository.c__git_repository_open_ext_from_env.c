#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_7__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int GIT_ERROR ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 char GIT_PATH_LIST_SEPARATOR ; 
 unsigned int GIT_REPOSITORY_OPEN_CROSS_FS ; 
 unsigned int GIT_REPOSITORY_OPEN_NO_DOTGIT ; 
 unsigned int GIT_REPOSITORY_OPEN_NO_SEARCH ; 
 int git__getenv (TYPE_1__*,char*) ; 
 char* git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_len (TYPE_1__*) ; 
 int git_config_parse_bool (int*,char*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_index_open (int /*<<< orphan*/ **,char*) ; 
 int git_odb_add_disk_alternate (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int git_odb_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_repository_open_ext (int /*<<< orphan*/ **,char const*,unsigned int,char const*) ; 
 int /*<<< orphan*/  git_repository_set_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository_set_namespace (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_set_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _git_repository_open_ext_from_env(
	git_repository **out,
	const char *start_path)
{
	git_repository *repo = NULL;
	git_index *index = NULL;
	git_odb *odb = NULL;
	git_buf dir_buf = GIT_BUF_INIT;
	git_buf ceiling_dirs_buf = GIT_BUF_INIT;
	git_buf across_fs_buf = GIT_BUF_INIT;
	git_buf index_file_buf = GIT_BUF_INIT;
	git_buf namespace_buf = GIT_BUF_INIT;
	git_buf object_dir_buf = GIT_BUF_INIT;
	git_buf alts_buf = GIT_BUF_INIT;
	git_buf work_tree_buf = GIT_BUF_INIT;
	git_buf common_dir_buf = GIT_BUF_INIT;
	const char *ceiling_dirs = NULL;
	unsigned flags = 0;
	int error;

	if (!start_path) {
		error = git__getenv(&dir_buf, "GIT_DIR");
		if (error == GIT_ENOTFOUND) {
			git_error_clear();
			start_path = ".";
		} else if (error < 0)
			goto error;
		else {
			start_path = git_buf_cstr(&dir_buf);
			flags |= GIT_REPOSITORY_OPEN_NO_SEARCH;
			flags |= GIT_REPOSITORY_OPEN_NO_DOTGIT;
		}
	}

	error = git__getenv(&ceiling_dirs_buf, "GIT_CEILING_DIRECTORIES");
	if (error == GIT_ENOTFOUND)
		git_error_clear();
	else if (error < 0)
		goto error;
	else
		ceiling_dirs = git_buf_cstr(&ceiling_dirs_buf);

	error = git__getenv(&across_fs_buf, "GIT_DISCOVERY_ACROSS_FILESYSTEM");
	if (error == GIT_ENOTFOUND)
		git_error_clear();
	else if (error < 0)
		goto error;
	else {
		int across_fs = 0;
		error = git_config_parse_bool(&across_fs, git_buf_cstr(&across_fs_buf));
		if (error < 0)
			goto error;
		if (across_fs)
			flags |= GIT_REPOSITORY_OPEN_CROSS_FS;
	}

	error = git__getenv(&index_file_buf, "GIT_INDEX_FILE");
	if (error == GIT_ENOTFOUND)
		git_error_clear();
	else if (error < 0)
		goto error;
	else {
		error = git_index_open(&index, git_buf_cstr(&index_file_buf));
		if (error < 0)
			goto error;
	}

	error = git__getenv(&namespace_buf, "GIT_NAMESPACE");
	if (error == GIT_ENOTFOUND)
		git_error_clear();
	else if (error < 0)
		goto error;

	error = git__getenv(&object_dir_buf, "GIT_OBJECT_DIRECTORY");
	if (error == GIT_ENOTFOUND)
		git_error_clear();
	else if (error < 0)
		goto error;
	else {
		error = git_odb_open(&odb, git_buf_cstr(&object_dir_buf));
		if (error < 0)
			goto error;
	}

	error = git__getenv(&work_tree_buf, "GIT_WORK_TREE");
	if (error == GIT_ENOTFOUND)
		git_error_clear();
	else if (error < 0)
		goto error;
	else {
		git_error_set(GIT_ERROR_INVALID, "GIT_WORK_TREE unimplemented");
		error = GIT_ERROR;
		goto error;
	}

	error = git__getenv(&work_tree_buf, "GIT_COMMON_DIR");
	if (error == GIT_ENOTFOUND)
		git_error_clear();
	else if (error < 0)
		goto error;
	else {
		git_error_set(GIT_ERROR_INVALID, "GIT_COMMON_DIR unimplemented");
		error = GIT_ERROR;
		goto error;
	}

	error = git_repository_open_ext(&repo, start_path, flags, ceiling_dirs);
	if (error < 0)
		goto error;

	if (odb)
		git_repository_set_odb(repo, odb);

	error = git__getenv(&alts_buf, "GIT_ALTERNATE_OBJECT_DIRECTORIES");
	if (error == GIT_ENOTFOUND) {
		git_error_clear();
		error = 0;
	} else if (error < 0)
		goto error;
        else {
		const char *end;
		char *alt, *sep;
		if (!odb) {
			error = git_repository_odb(&odb, repo);
			if (error < 0)
				goto error;
		}

		end = git_buf_cstr(&alts_buf) + git_buf_len(&alts_buf);
		for (sep = alt = alts_buf.ptr; sep != end; alt = sep+1) {
			for (sep = alt; *sep && *sep != GIT_PATH_LIST_SEPARATOR; sep++)
				;
			if (*sep)
				*sep = '\0';
			error = git_odb_add_disk_alternate(odb, alt);
			if (error < 0)
				goto error;
		}
	}

	if (git_buf_len(&namespace_buf)) {
		error = git_repository_set_namespace(repo, git_buf_cstr(&namespace_buf));
		if (error < 0)
			goto error;
	}

	git_repository_set_index(repo, index);

	if (out) {
		*out = repo;
		goto success;
	}
error:
	git_repository_free(repo);
success:
	git_odb_free(odb);
	git_index_free(index);
	git_buf_dispose(&common_dir_buf);
	git_buf_dispose(&work_tree_buf);
	git_buf_dispose(&alts_buf);
	git_buf_dispose(&object_dir_buf);
	git_buf_dispose(&namespace_buf);
	git_buf_dispose(&index_file_buf);
	git_buf_dispose(&across_fs_buf);
	git_buf_dispose(&ceiling_dirs_buf);
	git_buf_dispose(&dir_buf);
	return error;
}