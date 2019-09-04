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
struct hashmap_iter {int dummy; } ;
struct git_attr {size_t attr_nr; } ;
struct attr_hashmap {int /*<<< orphan*/  map; } ;
struct attr_hash_entry {struct git_attr* value; } ;
struct attr_check {unsigned int all_attrs_nr; TYPE_1__* all_attrs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * macro; int /*<<< orphan*/  value; struct git_attr const* attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR__UNKNOWN ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  REALLOC_ARRAY (TYPE_1__*,unsigned int) ; 
 unsigned int hashmap_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_iter_init (int /*<<< orphan*/ *,struct hashmap_iter*) ; 
 struct attr_hash_entry* hashmap_iter_next (struct hashmap_iter*) ; 
 int /*<<< orphan*/  hashmap_lock (struct attr_hashmap*) ; 
 int /*<<< orphan*/  hashmap_unlock (struct attr_hashmap*) ; 

__attribute__((used)) static void all_attrs_init(struct attr_hashmap *map, struct attr_check *check)
{
	int i;
	unsigned int size;

	hashmap_lock(map);

	size = hashmap_get_size(&map->map);
	if (size < check->all_attrs_nr)
		BUG("interned attributes shouldn't be deleted");

	/*
	 * If the number of attributes in the global dictionary has increased
	 * (or this attr_check instance doesn't have an initialized all_attrs
	 * field), reallocate the provided attr_check instance's all_attrs
	 * field and fill each entry with its corresponding git_attr.
	 */
	if (size != check->all_attrs_nr) {
		struct attr_hash_entry *e;
		struct hashmap_iter iter;
		hashmap_iter_init(&map->map, &iter);

		REALLOC_ARRAY(check->all_attrs, size);
		check->all_attrs_nr = size;

		while ((e = hashmap_iter_next(&iter))) {
			const struct git_attr *a = e->value;
			check->all_attrs[a->attr_nr].attr = a;
		}
	}

	hashmap_unlock(map);

	/*
	 * Re-initialize every entry in check->all_attrs.
	 * This re-initialization can live outside of the locked region since
	 * the attribute dictionary is no longer being accessed.
	 */
	for (i = 0; i < check->all_attrs_nr; i++) {
		check->all_attrs[i].value = ATTR__UNKNOWN;
		check->all_attrs[i].macro = NULL;
	}
}