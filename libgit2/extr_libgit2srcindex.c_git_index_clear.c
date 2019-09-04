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
struct TYPE_9__ {scalar_t__ length; } ;
struct TYPE_10__ {int dirty; int /*<<< orphan*/  stamp; TYPE_1__ entries; int /*<<< orphan*/  entries_map; int /*<<< orphan*/  tree_pool; int /*<<< orphan*/ * tree; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  git_futils_filestamp_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_idxmap_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_name_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_reuc_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_free_deleted (TYPE_2__*) ; 
 int index_remove_entry (TYPE_2__*,scalar_t__) ; 

int git_index_clear(git_index *index)
{
	int error = 0;

	assert(index);

	index->dirty = 1;
	index->tree = NULL;
	git_pool_clear(&index->tree_pool);

	git_idxmap_clear(index->entries_map);
	while (!error && index->entries.length > 0)
		error = index_remove_entry(index, index->entries.length - 1);
	index_free_deleted(index);

	git_index_reuc_clear(index);
	git_index_name_clear(index);

	git_futils_filestamp_set(&index->stamp, NULL);

	return error;
}