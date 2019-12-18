#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_7__ {scalar_t__ size; } ;
typedef  TYPE_1__ git_cached_obj ;
struct TYPE_8__ {int /*<<< orphan*/  used_memory; int /*<<< orphan*/  map; } ;
typedef  TYPE_2__ git_cache ;

/* Variables and functions */
 scalar_t__ GIT_ITEROVER ; 
 int /*<<< orphan*/  clear_cache (TYPE_2__*) ; 
 int /*<<< orphan*/  git_atomic_ssize_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_cache__current_storage ; 
 size_t git_cache_size (TYPE_2__*) ; 
 int /*<<< orphan*/  git_cached_obj_decref (TYPE_1__*) ; 
 int /*<<< orphan*/  git_oidmap_delete (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ git_oidmap_iterate (void**,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static void cache_evict_entries(git_cache *cache)
{
	size_t evict_count = git_cache_size(cache) / 2048, i;
	ssize_t evicted_memory = 0;

	if (evict_count < 8)
		evict_count = 8;

	/* do not infinite loop if there's not enough entries to evict  */
	if (evict_count > git_cache_size(cache)) {
		clear_cache(cache);
		return;
	}

	i = 0;
	while (evict_count > 0) {
		git_cached_obj *evict;
		const git_oid *key;

		if (git_oidmap_iterate((void **) &evict, cache->map, &i, &key) == GIT_ITEROVER)
			break;

		evict_count--;
		evicted_memory += evict->size;
		git_oidmap_delete(cache->map, key);
		git_cached_obj_decref(evict);
	}

	cache->used_memory -= evicted_memory;
	git_atomic_ssize_add(&git_cache__current_storage, -evicted_memory);
}