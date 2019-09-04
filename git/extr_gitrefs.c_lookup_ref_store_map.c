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
struct ref_store_hash_entry {struct ref_store* refs; } ;
struct ref_store {int dummy; } ;
struct hashmap {int /*<<< orphan*/  tablesize; } ;

/* Variables and functions */
 struct ref_store_hash_entry* hashmap_get_from_hash (struct hashmap*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strhash (char const*) ; 

__attribute__((used)) static struct ref_store *lookup_ref_store_map(struct hashmap *map,
					      const char *name)
{
	struct ref_store_hash_entry *entry;

	if (!map->tablesize)
		/* It's initialized on demand in register_ref_store(). */
		return NULL;

	entry = hashmap_get_from_hash(map, strhash(name), name);
	return entry ? entry->refs : NULL;
}