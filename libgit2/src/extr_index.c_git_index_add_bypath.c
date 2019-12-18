#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_13__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_2__ git_index ;
typedef  int /*<<< orphan*/  git_error_state ;

/* Variables and functions */
 int GIT_EDIRECTORY ; 
 int GIT_EEXISTS ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  INDEX_OWNER (TYPE_2__*) ; 
 int add_repo_as_submodule (TYPE_1__**,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_state_capture (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_error_state_free (int /*<<< orphan*/ *) ; 
 int git_error_state_restore (int /*<<< orphan*/ *) ; 
 int git_submodule_add_to_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_tree_cache_invalidate_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int index_conflict_to_reuc (TYPE_2__*,char const*) ; 
 int index_entry_init (TYPE_1__**,TYPE_2__*,char const*) ; 
 int index_insert (TYPE_2__*,TYPE_1__**,int,int,int,int) ; 

int git_index_add_bypath(git_index *index, const char *path)
{
	git_index_entry *entry = NULL;
	int ret;

	assert(index && path);

	if ((ret = index_entry_init(&entry, index, path)) == 0)
		ret = index_insert(index, &entry, 1, false, false, true);

	/* If we were given a directory, let's see if it's a submodule */
	if (ret < 0 && ret != GIT_EDIRECTORY)
		return ret;

	if (ret == GIT_EDIRECTORY) {
		git_submodule *sm;
		git_error_state err;

		git_error_state_capture(&err, ret);

		ret = git_submodule_lookup(&sm, INDEX_OWNER(index), path);
		if (ret == GIT_ENOTFOUND)
			return git_error_state_restore(&err);

		git_error_state_free(&err);

		/*
		 * EEXISTS means that there is a repository at that path, but it's not known
		 * as a submodule. We add its HEAD as an entry and don't register it.
		 */
		if (ret == GIT_EEXISTS) {
			if ((ret = add_repo_as_submodule(&entry, index, path)) < 0)
				return ret;

			if ((ret = index_insert(index, &entry, 1, false, false, true)) < 0)
				return ret;
		} else if (ret < 0) {
			return ret;
		} else {
			ret = git_submodule_add_to_index(sm, false);
			git_submodule_free(sm);
			return ret;
		}
	}

	/* Adding implies conflict was resolved, move conflict entries to REUC */
	if ((ret = index_conflict_to_reuc(index, path)) < 0 && ret != GIT_ENOTFOUND)
		return ret;

	git_tree_cache_invalidate_path(index->tree, entry->path);
	return 0;
}