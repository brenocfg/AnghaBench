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
struct hashmap {struct hashmap_entry** table; } ;

/* Variables and functions */
 size_t bucket (struct hashmap const*,struct hashmap_entry const*) ; 
 int /*<<< orphan*/  entry_equals (struct hashmap const*,struct hashmap_entry*,struct hashmap_entry const*,void const*) ; 

__attribute__((used)) static inline struct hashmap_entry **find_entry_ptr(const struct hashmap *map,
		const struct hashmap_entry *key, const void *keydata)
{
	struct hashmap_entry **e = &map->table[bucket(map, key)];
	while (*e && !entry_equals(map, *e, key, keydata))
		e = &(*e)->next;
	return e;
}