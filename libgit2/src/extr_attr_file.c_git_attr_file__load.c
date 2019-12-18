#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_off_t ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  scalar_t__ git_bom_t ;
typedef  int /*<<< orphan*/  git_blob ;
struct TYPE_14__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ git_attr_session ;
typedef  int const git_attr_file_source ;
typedef  int (* git_attr_file_parser ) (int /*<<< orphan*/ *,TYPE_3__*,char const*,int) ;
struct TYPE_16__ {int /*<<< orphan*/  path; int /*<<< orphan*/  fullpath; } ;
typedef  TYPE_4__ git_attr_file_entry ;
struct TYPE_13__ {int /*<<< orphan*/  stamp; int /*<<< orphan*/  oid; } ;
struct TYPE_15__ {int nonexistent; TYPE_1__ cache_data; int /*<<< orphan*/  session_key; } ;
typedef  TYPE_3__ git_attr_file ;

/* Variables and functions */
#define  GIT_ATTR_FILE__FROM_FILE 131 
#define  GIT_ATTR_FILE__FROM_HEAD 130 
#define  GIT_ATTR_FILE__FROM_INDEX 129 
#define  GIT_ATTR_FILE__IN_MEMORY 128 
 scalar_t__ GIT_BOM_UTF8 ; 
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_BLOBSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int attr_file_oid_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_attr_file__free (TYPE_3__*) ; 
 int git_attr_file__new (TYPE_3__**,TYPE_4__*,int const) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_id (int /*<<< orphan*/ *) ; 
 int git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawsize (int /*<<< orphan*/ *) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int git_buf_text_detect_bom (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  git_futils_filestamp_set_from_stat (int /*<<< orphan*/ *,struct stat*) ; 
 int git_futils_open_ro (int /*<<< orphan*/ ) ; 
 int git_futils_readbuffer_fd (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_tree_entry_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int /*<<< orphan*/  p_stat (int /*<<< orphan*/ ,struct stat*) ; 

int git_attr_file__load(
	git_attr_file **out,
	git_repository *repo,
	git_attr_session *attr_session,
	git_attr_file_entry *entry,
	git_attr_file_source source,
	git_attr_file_parser parser,
	bool allow_macros)
{
	int error = 0;
	git_tree *tree = NULL;
	git_tree_entry *tree_entry = NULL;
	git_blob *blob = NULL;
	git_buf content = GIT_BUF_INIT;
	const char *content_str;
	git_attr_file *file;
	struct stat st;
	bool nonexistent = false;
	int bom_offset;
	git_bom_t bom;
	git_oid id;
	git_off_t blobsize;

	*out = NULL;

	switch (source) {
	case GIT_ATTR_FILE__IN_MEMORY:
		/* in-memory attribute file doesn't need data */
		break;
	case GIT_ATTR_FILE__FROM_INDEX: {
		if ((error = attr_file_oid_from_index(&id, repo, entry->path)) < 0 ||
			(error = git_blob_lookup(&blob, repo, &id)) < 0)
			return error;

		/* Do not assume that data straight from the ODB is NULL-terminated;
		 * copy the contents of a file to a buffer to work on */
		blobsize = git_blob_rawsize(blob);

		GIT_ERROR_CHECK_BLOBSIZE(blobsize);
		git_buf_put(&content, git_blob_rawcontent(blob), (size_t)blobsize);
		break;
	}
	case GIT_ATTR_FILE__FROM_FILE: {
		int fd = -1;

		/* For open or read errors, pretend that we got ENOTFOUND. */
		/* TODO: issue warning when warning API is available */

		if (p_stat(entry->fullpath, &st) < 0 ||
			S_ISDIR(st.st_mode) ||
			(fd = git_futils_open_ro(entry->fullpath)) < 0 ||
			(error = git_futils_readbuffer_fd(&content, fd, (size_t)st.st_size)) < 0)
			nonexistent = true;

		if (fd >= 0)
			p_close(fd);

		break;
	}
	case GIT_ATTR_FILE__FROM_HEAD: {
		if ((error = git_repository_head_tree(&tree, repo)) < 0 ||
		    (error = git_tree_entry_bypath(&tree_entry, tree, entry->path)) < 0 ||
		    (error = git_blob_lookup(&blob, repo, git_tree_entry_id(tree_entry))) < 0)
			goto cleanup;

		/*
		 * Do not assume that data straight from the ODB is NULL-terminated;
		 * copy the contents of a file to a buffer to work on.
		 */
		blobsize = git_blob_rawsize(blob);

		GIT_ERROR_CHECK_BLOBSIZE(blobsize);
		if ((error = git_buf_put(&content,
			git_blob_rawcontent(blob), (size_t)blobsize)) < 0)
			goto cleanup;

		break;
	}
	default:
		git_error_set(GIT_ERROR_INVALID, "unknown file source %d", source);
		return -1;
	}

	if ((error = git_attr_file__new(&file, entry, source)) < 0)
		goto cleanup;

	/* advance over a UTF8 BOM */
	content_str = git_buf_cstr(&content);
	bom_offset = git_buf_text_detect_bom(&bom, &content);

	if (bom == GIT_BOM_UTF8)
		content_str += bom_offset;

	/* store the key of the attr_reader; don't bother with cache
	 * invalidation during the same attr reader session.
	 */
	if (attr_session)
		file->session_key = attr_session->key;

	if (parser && (error = parser(repo, file, content_str, allow_macros)) < 0) {
		git_attr_file__free(file);
		goto cleanup;
	}

	/* write cache breakers */
	if (nonexistent)
		file->nonexistent = 1;
	else if (source == GIT_ATTR_FILE__FROM_INDEX)
		git_oid_cpy(&file->cache_data.oid, git_blob_id(blob));
	else if (source == GIT_ATTR_FILE__FROM_HEAD)
		git_oid_cpy(&file->cache_data.oid, git_tree_id(tree));
	else if (source == GIT_ATTR_FILE__FROM_FILE)
		git_futils_filestamp_set_from_stat(&file->cache_data.stamp, &st);
	/* else always cacheable */

	*out = file;

cleanup:
	git_blob_free(blob);
	git_tree_entry_free(tree_entry);
	git_tree_free(tree);
	git_buf_dispose(&content);

	return error;
}