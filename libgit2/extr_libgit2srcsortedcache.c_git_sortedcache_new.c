#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector_cmp ;
typedef  int /*<<< orphan*/  git_sortedcache_free_item_fn ;
struct TYPE_7__ {size_t item_path_offset; int /*<<< orphan*/  pool; int /*<<< orphan*/  items; int /*<<< orphan*/  map; int /*<<< orphan*/  path; void* free_item_payload; int /*<<< orphan*/  free_item; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ git_sortedcache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,size_t) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strmap_free (int /*<<< orphan*/ ) ; 
 scalar_t__ git_strmap_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int git_sortedcache_new(
	git_sortedcache **out,
	size_t item_path_offset,
	git_sortedcache_free_item_fn free_item,
	void *free_item_payload,
	git_vector_cmp item_cmp,
	const char *path)
{
	git_sortedcache *sc;
	size_t pathlen, alloclen;

	pathlen = path ? strlen(path) : 0;

	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, sizeof(git_sortedcache), pathlen);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, alloclen, 1);
	sc = git__calloc(1, alloclen);
	GIT_ERROR_CHECK_ALLOC(sc);

	git_pool_init(&sc->pool, 1);

	if (git_vector_init(&sc->items, 4, item_cmp) < 0 ||
	    git_strmap_new(&sc->map) < 0)
		goto fail;

	if (git_rwlock_init(&sc->lock)) {
		git_error_set(GIT_ERROR_OS, "failed to initialize lock");
		goto fail;
	}

	sc->item_path_offset  = item_path_offset;
	sc->free_item         = free_item;
	sc->free_item_payload = free_item_payload;
	GIT_REFCOUNT_INC(sc);
	if (pathlen)
		memcpy(sc->path, path, pathlen);

	*out = sc;
	return 0;

fail:
	git_strmap_free(sc->map);
	git_vector_free(&sc->items);
	git_pool_clear(&sc->pool);
	git__free(sc);
	return -1;
}