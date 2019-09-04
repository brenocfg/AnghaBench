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
typedef  int /*<<< orphan*/  git_treebuilder ;
struct TYPE_10__ {scalar_t__ entry_count; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ git_tree_cache ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_11__ {char const* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_index_entry ;
struct TYPE_12__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_3__ git_index ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int append_entry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ find_next_dir (char const*,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__strndup (char*,int) ; 
 size_t git_index_entrycount (TYPE_3__*) ; 
 TYPE_2__* git_index_get_byindex (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* git_tree_cache_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_treebuilder_write_with_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int write_tree(
	git_oid *oid,
	git_repository *repo,
	git_index *index,
	const char *dirname,
	size_t start,
	git_buf *shared_buf)
{
	git_treebuilder *bld = NULL;
	size_t i, entries = git_index_entrycount(index);
	int error;
	size_t dirname_len = strlen(dirname);
	const git_tree_cache *cache;

	cache = git_tree_cache_get(index->tree, dirname);
	if (cache != NULL && cache->entry_count >= 0){
		git_oid_cpy(oid, &cache->oid);
		return (int)find_next_dir(dirname, index, start);
	}

	if ((error = git_treebuilder_new(&bld, repo, NULL)) < 0 || bld == NULL)
		return -1;

	/*
	 * This loop is unfortunate, but necessary. The index doesn't have
	 * any directores, so we need to handle that manually, and we
	 * need to keep track of the current position.
	 */
	for (i = start; i < entries; ++i) {
		const git_index_entry *entry = git_index_get_byindex(index, i);
		const char *filename, *next_slash;

	/*
	 * If we've left our (sub)tree, exit the loop and return. The
	 * first check is an early out (and security for the
	 * third). The second check is a simple prefix comparison. The
	 * third check catches situations where there is a directory
	 * win32/sys and a file win32mmap.c. Without it, the following
	 * code believes there is a file win32/mmap.c
	 */
		if (strlen(entry->path) < dirname_len ||
		    memcmp(entry->path, dirname, dirname_len) ||
		    (dirname_len > 0 && entry->path[dirname_len] != '/')) {
			break;
		}

		filename = entry->path + dirname_len;
		if (*filename == '/')
			filename++;
		next_slash = strchr(filename, '/');
		if (next_slash) {
			git_oid sub_oid;
			int written;
			char *subdir, *last_comp;

			subdir = git__strndup(entry->path, next_slash - entry->path);
			GIT_ERROR_CHECK_ALLOC(subdir);

			/* Write out the subtree */
			written = write_tree(&sub_oid, repo, index, subdir, i, shared_buf);
			if (written < 0) {
				git__free(subdir);
				goto on_error;
			} else {
				i = written - 1; /* -1 because of the loop increment */
			}

			/*
			 * We need to figure out what we want toinsert
			 * into this tree. If we're traversing
			 * deps/zlib/, then we only want to write
			 * 'zlib' into the tree.
			 */
			last_comp = strrchr(subdir, '/');
			if (last_comp) {
				last_comp++; /* Get rid of the '/' */
			} else {
				last_comp = subdir;
			}

			error = append_entry(bld, last_comp, &sub_oid, S_IFDIR, true);
			git__free(subdir);
			if (error < 0)
				goto on_error;
		} else {
			error = append_entry(bld, filename, &entry->id, entry->mode, true);
			if (error < 0)
				goto on_error;
		}
	}

	if (git_treebuilder_write_with_buffer(oid, bld, shared_buf) < 0)
		goto on_error;

	git_treebuilder_free(bld);
	return (int)i;

on_error:
	git_treebuilder_free(bld);
	return -1;
}