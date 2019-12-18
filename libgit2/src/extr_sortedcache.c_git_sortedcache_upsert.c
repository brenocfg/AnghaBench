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
struct TYPE_3__ {size_t item_path_offset; int /*<<< orphan*/  map; int /*<<< orphan*/  items; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ git_sortedcache ;

/* Variables and functions */
 void* git_pool_mallocz (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_strmap_delete (int /*<<< orphan*/ ,char*) ; 
 void* git_strmap_get (int /*<<< orphan*/ ,char const*) ; 
 int git_strmap_set (int /*<<< orphan*/ ,char*,void*) ; 
 int git_vector_insert (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int git_sortedcache_upsert(void **out, git_sortedcache *sc, const char *key)
{
	size_t keylen, itemlen;
	int error = 0;
	char *item_key;
	void *item;

	if ((item = git_strmap_get(sc->map, key)) != NULL)
		goto done;

	keylen  = strlen(key);
	itemlen = sc->item_path_offset + keylen + 1;
	itemlen = (itemlen + 7) & ~7;

	if ((item = git_pool_mallocz(&sc->pool, itemlen)) == NULL) {
		/* don't use GIT_ERROR_CHECK_ALLOC b/c of lock */
		error = -1;
		goto done;
	}

	/* one strange thing is that even if the vector or hash table insert
	 * fail, there is no way to free the pool item so we just abandon it
	 */

	item_key = ((char *)item) + sc->item_path_offset;
	memcpy(item_key, key, keylen);

	if ((error = git_strmap_set(sc->map, item_key, item)) < 0)
		goto done;

	if ((error = git_vector_insert(&sc->items, item)) < 0)
		git_strmap_delete(sc->map, item_key);

done:
	if (out)
		*out = !error ? item : NULL;
	return error;
}