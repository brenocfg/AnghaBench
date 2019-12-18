#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_13__ {scalar_t__ path; scalar_t__ file_size; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_14__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/ * INDEX_OWNER (TYPE_2__*) ; 
 size_t UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int create_index_error (int,char*) ; 
 int git_blob_create_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_cache_invalidate_path (int /*<<< orphan*/ ,scalar_t__) ; 
 int index_conflict_to_reuc (TYPE_2__*,scalar_t__) ; 
 scalar_t__ index_entry_dup (TYPE_1__**,TYPE_2__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  index_entry_free (TYPE_1__*) ; 
 int index_insert (TYPE_2__*,TYPE_1__**,int,int,int,int) ; 
 int /*<<< orphan*/  is_file_or_link (int /*<<< orphan*/ ) ; 

int git_index_add_from_buffer(
    git_index *index, const git_index_entry *source_entry,
    const void *buffer, size_t len)
{
	git_index_entry *entry = NULL;
	int error = 0;
	git_oid id;

	assert(index && source_entry->path);

	if (INDEX_OWNER(index) == NULL)
		return create_index_error(-1,
			"could not initialize index entry. "
			"Index is not backed up by an existing repository.");

	if (!is_file_or_link(source_entry->mode)) {
		git_error_set(GIT_ERROR_INDEX, "invalid filemode");
		return -1;
	}

	if (len > UINT32_MAX) {
		git_error_set(GIT_ERROR_INDEX, "buffer is too large");
		return -1;
	}

	if (index_entry_dup(&entry, index, source_entry) < 0)
		return -1;

	error = git_blob_create_from_buffer(&id, INDEX_OWNER(index), buffer, len);
	if (error < 0) {
		index_entry_free(entry);
		return error;
	}

	git_oid_cpy(&entry->id, &id);
	entry->file_size = (uint32_t)len;

	if ((error = index_insert(index, &entry, 1, true, true, true)) < 0)
		return error;

	/* Adding implies conflict was resolved, move conflict entries to REUC */
	if ((error = index_conflict_to_reuc(index, entry->path)) < 0 && error != GIT_ENOTFOUND)
		return error;

	git_tree_cache_invalidate_path(index->tree, entry->path);
	return 0;
}