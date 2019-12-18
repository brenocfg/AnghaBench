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
struct cache_dir {int dummy; } ;
struct cache {struct cache* next_local; } ;

/* Variables and functions */
 struct cache_dir* cacheinfo_create_cache_dir (unsigned int) ; 
 int /*<<< orphan*/  cacheinfo_create_index_dir (struct cache*,int,struct cache_dir*) ; 

__attribute__((used)) static void cacheinfo_sysfs_populate(unsigned int cpu_id,
				     struct cache *cache_list)
{
	struct cache_dir *cache_dir;
	struct cache *cache;
	int index = 0;

	cache_dir = cacheinfo_create_cache_dir(cpu_id);
	if (!cache_dir)
		return;

	cache = cache_list;
	while (cache) {
		cacheinfo_create_index_dir(cache, index, cache_dir);
		index++;
		cache = cache->next_local;
	}
}