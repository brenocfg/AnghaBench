#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ path; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_11__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_cache_invalidate_path (int /*<<< orphan*/ ,scalar_t__) ; 
 int index_entry_dup (TYPE_1__**,TYPE_2__*,TYPE_1__ const*) ; 
 int index_insert (TYPE_2__*,TYPE_1__**,int,int,int,int) ; 
 int /*<<< orphan*/  valid_filemode (int /*<<< orphan*/ ) ; 

int git_index_add(git_index *index, const git_index_entry *source_entry)
{
	git_index_entry *entry = NULL;
	int ret;

	assert(index && source_entry && source_entry->path);

	if (!valid_filemode(source_entry->mode)) {
		git_error_set(GIT_ERROR_INDEX, "invalid entry mode");
		return -1;
	}

	if ((ret = index_entry_dup(&entry, index, source_entry)) < 0 ||
		(ret = index_insert(index, &entry, 1, true, true, false)) < 0)
		return ret;

	git_tree_cache_invalidate_path(index->tree, entry->path);
	return 0;
}