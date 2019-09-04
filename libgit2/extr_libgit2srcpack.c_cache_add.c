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
struct TYPE_14__ {scalar_t__ len; } ;
typedef  TYPE_2__ git_rawobj ;
struct TYPE_13__ {scalar_t__ len; } ;
struct TYPE_15__ {TYPE_1__ raw; } ;
typedef  TYPE_3__ git_pack_cache_entry ;
struct TYPE_16__ {scalar_t__ memory_used; scalar_t__ memory_limit; int /*<<< orphan*/  lock; int /*<<< orphan*/  entries; } ;
typedef  TYPE_4__ git_pack_cache ;
typedef  int /*<<< orphan*/  git_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 scalar_t__ GIT_PACK_CACHE_SIZE_LIMIT ; 
 int /*<<< orphan*/  free_lowest_entry (TYPE_4__*) ; 
 int /*<<< orphan*/  git__free (TYPE_3__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 
 int git_offmap_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_offmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* new_cache_object (TYPE_2__*) ; 

__attribute__((used)) static int cache_add(
		git_pack_cache_entry **cached_out,
		git_pack_cache *cache,
		git_rawobj *base,
		git_off_t offset)
{
	git_pack_cache_entry *entry;
	int exists;

	if (base->len > GIT_PACK_CACHE_SIZE_LIMIT)
		return -1;

	entry = new_cache_object(base);
	if (entry) {
		if (git_mutex_lock(&cache->lock) < 0) {
			git_error_set(GIT_ERROR_OS, "failed to lock cache");
			git__free(entry);
			return -1;
		}
		/* Add it to the cache if nobody else has */
		exists = git_offmap_exists(cache->entries, offset);
		if (!exists) {
			while (cache->memory_used + base->len > cache->memory_limit)
				free_lowest_entry(cache);

			git_offmap_set(cache->entries, offset, entry);
			cache->memory_used += entry->raw.len;

			*cached_out = entry;
		}
		git_mutex_unlock(&cache->lock);
		/* Somebody beat us to adding it into the cache */
		if (exists) {
			git__free(entry);
			return -1;
		}
	}

	return 0;
}