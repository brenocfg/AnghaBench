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
struct hashmap_entry {struct hashmap_entry* next; } ;
struct hashmap {scalar_t__ private_size; scalar_t__ grow_at; int tablesize; scalar_t__ do_count_items; struct hashmap_entry** table; } ;

/* Variables and functions */
 int HASHMAP_RESIZE_BITS ; 
 unsigned int bucket (struct hashmap*,struct hashmap_entry*) ; 
 int /*<<< orphan*/  rehash (struct hashmap*,int) ; 

void hashmap_add(struct hashmap *map, struct hashmap_entry *entry)
{
	unsigned int b = bucket(map, entry);

	/* add entry */
	entry->next = map->table[b];
	map->table[b] = entry;

	/* fix size and rehash if appropriate */
	if (map->do_count_items) {
		map->private_size++;
		if (map->private_size > map->grow_at)
			rehash(map, map->tablesize << HASHMAP_RESIZE_BITS);
	}
}