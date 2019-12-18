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
struct hashmap {unsigned int tablesize; struct hashmap_entry** table; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_table (struct hashmap*,unsigned int) ; 
 unsigned int bucket (struct hashmap*,struct hashmap_entry*) ; 
 int /*<<< orphan*/  free (struct hashmap_entry**) ; 

__attribute__((used)) static void rehash(struct hashmap *map, unsigned int newsize)
{
	unsigned int i, oldsize = map->tablesize;
	struct hashmap_entry **oldtable = map->table;

	alloc_table(map, newsize);
	for (i = 0; i < oldsize; i++) {
		struct hashmap_entry *e = oldtable[i];
		while (e) {
			struct hashmap_entry *next = e->next;
			unsigned int b = bucket(map, e);
			e->next = map->table[b];
			map->table[b] = e;
			e = next;
		}
	}
	free(oldtable);
}