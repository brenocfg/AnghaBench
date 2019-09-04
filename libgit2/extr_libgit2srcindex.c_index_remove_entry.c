#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_10__ {int dirty; int /*<<< orphan*/  deleted; int /*<<< orphan*/  readers; int /*<<< orphan*/  entries; int /*<<< orphan*/  tree; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE_IN_MAP (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ git_atomic_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_cache_invalidate_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 int git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int git_vector_remove (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  index_entry_free (TYPE_1__*) ; 

__attribute__((used)) static int index_remove_entry(git_index *index, size_t pos)
{
	int error = 0;
	git_index_entry *entry = git_vector_get(&index->entries, pos);

	if (entry != NULL) {
		git_tree_cache_invalidate_path(index->tree, entry->path);
		DELETE_IN_MAP(index, entry);
	}

	error = git_vector_remove(&index->entries, pos);

	if (!error) {
		if (git_atomic_get(&index->readers) > 0) {
			error = git_vector_insert(&index->deleted, entry);
		} else {
			index_entry_free(entry);
		}

		index->dirty = 1;
	}

	return error;
}