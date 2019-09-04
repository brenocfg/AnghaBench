#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int on_disk; int /*<<< orphan*/  tree_pool; int /*<<< orphan*/  version; int /*<<< orphan*/  reuc_search; int /*<<< orphan*/  entries_search_path; int /*<<< orphan*/  entries_search; int /*<<< orphan*/  entries_cmp_path; int /*<<< orphan*/  deleted; int /*<<< orphan*/  reuc; int /*<<< orphan*/  names; int /*<<< orphan*/  entries_map; int /*<<< orphan*/  entries; int /*<<< orphan*/  index_file_path; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 int /*<<< orphan*/  INDEX_VERSION_NUMBER_DEFAULT ; 
 int /*<<< orphan*/  assert (TYPE_1__**) ; 
 int /*<<< orphan*/  conflict_name_cmp ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__strcmp_cb ; 
 int /*<<< orphan*/  git__strdup (char const*) ; 
 scalar_t__ git_idxmap_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_entry_cmp ; 
 int /*<<< orphan*/  git_index_entry_srch ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int git_index_read (TYPE_1__*,int) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_entry_srch_path ; 
 int /*<<< orphan*/  reuc_cmp ; 
 int /*<<< orphan*/  reuc_srch ; 

int git_index_open(git_index **index_out, const char *index_path)
{
	git_index *index;
	int error = -1;

	assert(index_out);

	index = git__calloc(1, sizeof(git_index));
	GIT_ERROR_CHECK_ALLOC(index);

	git_pool_init(&index->tree_pool, 1);

	if (index_path != NULL) {
		index->index_file_path = git__strdup(index_path);
		if (!index->index_file_path)
			goto fail;

		/* Check if index file is stored on disk already */
		if (git_path_exists(index->index_file_path) == true)
			index->on_disk = 1;
	}

	if (git_vector_init(&index->entries, 32, git_index_entry_cmp) < 0 ||
	    git_idxmap_new(&index->entries_map) < 0 ||
	    git_vector_init(&index->names, 8, conflict_name_cmp) < 0 ||
	    git_vector_init(&index->reuc, 8, reuc_cmp) < 0 ||
	    git_vector_init(&index->deleted, 8, git_index_entry_cmp) < 0)
		goto fail;

	index->entries_cmp_path = git__strcmp_cb;
	index->entries_search = git_index_entry_srch;
	index->entries_search_path = index_entry_srch_path;
	index->reuc_search = reuc_srch;
	index->version = INDEX_VERSION_NUMBER_DEFAULT;

	if (index_path != NULL && (error = git_index_read(index, true)) < 0)
		goto fail;

	*index_out = index;
	GIT_REFCOUNT_INC(index);

	return 0;

fail:
	git_pool_clear(&index->tree_pool);
	git_index_free(index);
	return error;
}