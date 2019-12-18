#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct name_cache {int size; TYPE_1__* cache; int /*<<< orphan*/  hits; int /*<<< orphan*/  probes; } ;
typedef  char* lookup_fn ;
typedef  int id_t ;
struct TYPE_2__ {char const* name; int id; } ;

/* Variables and functions */
 char const* NO_NAME ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static const char *
lookup_name(struct name_cache *cache,
    const char * (*lookup_fn)(struct name_cache *, id_t), id_t id)
{
	const char *name;
	int slot;


	cache->probes++;

	slot = id % cache->size;
	if (cache->cache[slot].name != NULL) {
		if (cache->cache[slot].id == id) {
			cache->hits++;
			if (cache->cache[slot].name == NO_NAME)
				return (NULL);
			return (cache->cache[slot].name);
		}
		if (cache->cache[slot].name != NO_NAME)
			free((void *)(uintptr_t)cache->cache[slot].name);
		cache->cache[slot].name = NULL;
	}

	name = (lookup_fn)(cache, id);
	if (name == NULL) {
		/* Cache and return the negative response. */
		cache->cache[slot].name = NO_NAME;
		cache->cache[slot].id = id;
		return (NULL);
	}

	cache->cache[slot].name = name;
	cache->cache[slot].id = id;
	return (cache->cache[slot].name);
}