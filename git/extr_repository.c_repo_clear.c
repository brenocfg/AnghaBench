#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct repository {int /*<<< orphan*/ * index; int /*<<< orphan*/ * submodule_cache; int /*<<< orphan*/ * config; int /*<<< orphan*/ * parsed_objects; int /*<<< orphan*/ * objects; int /*<<< orphan*/ * submodule_prefix; int /*<<< orphan*/ * worktree; int /*<<< orphan*/ * index_file; int /*<<< orphan*/ * graft_file; int /*<<< orphan*/ * commondir; int /*<<< orphan*/ * gitdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_configset_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parsed_object_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_object_store_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submodule_cache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_index ; 

void repo_clear(struct repository *repo)
{
	FREE_AND_NULL(repo->gitdir);
	FREE_AND_NULL(repo->commondir);
	FREE_AND_NULL(repo->graft_file);
	FREE_AND_NULL(repo->index_file);
	FREE_AND_NULL(repo->worktree);
	FREE_AND_NULL(repo->submodule_prefix);

	raw_object_store_clear(repo->objects);
	FREE_AND_NULL(repo->objects);

	parsed_object_pool_clear(repo->parsed_objects);
	FREE_AND_NULL(repo->parsed_objects);

	if (repo->config) {
		git_configset_clear(repo->config);
		FREE_AND_NULL(repo->config);
	}

	if (repo->submodule_cache) {
		submodule_cache_free(repo->submodule_cache);
		repo->submodule_cache = NULL;
	}

	if (repo->index) {
		discard_index(repo->index);
		if (repo->index != &the_index)
			FREE_AND_NULL(repo->index);
	}
}