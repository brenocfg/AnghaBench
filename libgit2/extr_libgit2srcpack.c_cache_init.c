#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * entries; int /*<<< orphan*/  lock; int /*<<< orphan*/  memory_limit; } ;
typedef  TYPE_1__ git_pack_cache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_PACK_CACHE_MEMORY_LIMIT ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ git_offmap_new (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int cache_init(git_pack_cache *cache)
{
	if (git_offmap_new(&cache->entries) < 0)
		return -1;

	cache->memory_limit = GIT_PACK_CACHE_MEMORY_LIMIT;

	if (git_mutex_init(&cache->lock)) {
		git_error_set(GIT_ERROR_OS, "failed to initialize pack cache mutex");

		git__free(cache->entries);
		cache->entries = NULL;

		return -1;
	}

	return 0;
}