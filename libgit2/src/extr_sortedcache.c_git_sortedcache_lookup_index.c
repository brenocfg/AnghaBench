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
struct sortedcache_magic_key {char const* key; int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  items; int /*<<< orphan*/  item_path_offset; } ;
typedef  TYPE_1__ git_sortedcache ;

/* Variables and functions */
 int git_vector_bsearch2 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sortedcache_magic_key*) ; 
 int /*<<< orphan*/  sortedcache_magic_cmp ; 

int git_sortedcache_lookup_index(
	size_t *out, git_sortedcache *sc, const char *key)
{
	struct sortedcache_magic_key magic;

	magic.offset = sc->item_path_offset;
	magic.key    = key;

	return git_vector_bsearch2(out, &sc->items, sortedcache_magic_cmp, &magic);
}