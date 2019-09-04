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
struct submodule_entry {int dummy; } ;
struct submodule_cache {scalar_t__ gitmodules_read; scalar_t__ initialized; int /*<<< orphan*/  for_name; int /*<<< orphan*/  for_path; } ;
struct hashmap_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_one_config (struct submodule_entry*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hashmap_iter_init (int /*<<< orphan*/ *,struct hashmap_iter*) ; 
 struct submodule_entry* hashmap_iter_next (struct hashmap_iter*) ; 

__attribute__((used)) static void submodule_cache_clear(struct submodule_cache *cache)
{
	struct hashmap_iter iter;
	struct submodule_entry *entry;

	if (!cache->initialized)
		return;

	/*
	 * We iterate over the name hash here to be symmetric with the
	 * allocation of struct submodule entries. Each is allocated by
	 * their .gitmodules blob sha1 and submodule name.
	 */
	hashmap_iter_init(&cache->for_name, &iter);
	while ((entry = hashmap_iter_next(&iter)))
		free_one_config(entry);

	hashmap_free(&cache->for_path, 1);
	hashmap_free(&cache->for_name, 1);
	cache->initialized = 0;
	cache->gitmodules_read = 0;
}