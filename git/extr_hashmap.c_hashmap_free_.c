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
struct hashmap_iter {int dummy; } ;
struct hashmap_entry {int dummy; } ;
struct hashmap {char* table; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 struct hashmap_entry* hashmap_iter_next (struct hashmap_iter*) ; 
 int /*<<< orphan*/  memset (struct hashmap*,int /*<<< orphan*/ ,int) ; 

void hashmap_free_(struct hashmap *map, ssize_t entry_offset)
{
	if (!map || !map->table)
		return;
	if (entry_offset >= 0) { /* called by hashmap_free_entries */
		struct hashmap_iter iter;
		struct hashmap_entry *e;

		hashmap_iter_init(map, &iter);
		while ((e = hashmap_iter_next(&iter)))
			/*
			 * like container_of, but using caller-calculated
			 * offset (caller being hashmap_free_entries)
			 */
			free((char *)e - entry_offset);
	}
	free(map->table);
	memset(map, 0, sizeof(*map));
}