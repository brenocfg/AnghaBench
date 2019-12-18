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
struct cpio {int dummy; } ;
typedef  int id_t ;
typedef  int /*<<< orphan*/  asnum ;
struct TYPE_2__ {char const* name; int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct name_cache* calloc (int,int) ; 
 int /*<<< orphan*/  free (char const*) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*) ; 
 int name_cache_size ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 char const* strdup (char const*) ; 

__attribute__((used)) static const char *
lookup_name(struct cpio *cpio, struct name_cache **name_cache_variable,
    int (*lookup_fn)(struct cpio *, const char **, id_t), id_t id)
{
	char asnum[16];
	struct name_cache	*cache;
	const char *name;
	int slot;


	if (*name_cache_variable == NULL) {
		*name_cache_variable = calloc(1, sizeof(struct name_cache));
		if (*name_cache_variable == NULL)
			lafe_errc(1, ENOMEM, "No more memory");
		(*name_cache_variable)->size = name_cache_size;
	}

	cache = *name_cache_variable;
	cache->probes++;

	slot = id % cache->size;
	if (cache->cache[slot].name != NULL) {
		if (cache->cache[slot].id == id) {
			cache->hits++;
			return (cache->cache[slot].name);
		}
		free(cache->cache[slot].name);
		cache->cache[slot].name = NULL;
	}

	if (lookup_fn(cpio, &name, id)) {
		/* If lookup failed, format it as a number. */
		snprintf(asnum, sizeof(asnum), "%u", (unsigned)id);
		name = asnum;
	}

	cache->cache[slot].name = strdup(name);
	if (cache->cache[slot].name != NULL) {
		cache->cache[slot].id = id;
		return (cache->cache[slot].name);
	}

	/*
	 * Conveniently, NULL marks an empty slot, so
	 * if the strdup() fails, we've just failed to
	 * cache it.  No recovery necessary.
	 */
	return (NULL);
}