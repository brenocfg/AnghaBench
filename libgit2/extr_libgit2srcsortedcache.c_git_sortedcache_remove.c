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
struct TYPE_3__ {int item_path_offset; int /*<<< orphan*/  free_item_payload; int /*<<< orphan*/  (* free_item ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  map; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ git_sortedcache ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_strmap_delete (int /*<<< orphan*/ ,char*) ; 
 char* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_vector_remove (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

int git_sortedcache_remove(git_sortedcache *sc, size_t pos)
{
	char *item;

	/*
	 * Because of pool allocation, this can't actually remove the item,
	 * but we can remove it from the items vector and the hash table.
	 */

	if ((item = git_vector_get(&sc->items, pos)) == NULL) {
		git_error_set(GIT_ERROR_INVALID, "removing item out of range");
		return GIT_ENOTFOUND;
	}

	(void)git_vector_remove(&sc->items, pos);

	git_strmap_delete(sc->map, item + sc->item_path_offset);

	if (sc->free_item)
		sc->free_item(sc->free_item_payload, item);

	return 0;
}