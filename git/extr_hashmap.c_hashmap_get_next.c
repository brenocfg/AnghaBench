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
struct hashmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ entry_equals (struct hashmap const*,struct hashmap_entry const*,struct hashmap_entry*,int /*<<< orphan*/ *) ; 

struct hashmap_entry *hashmap_get_next(const struct hashmap *map,
			const struct hashmap_entry *entry)
{
	struct hashmap_entry *e = entry->next;
	for (; e; e = e->next)
		if (entry_equals(map, entry, e, NULL))
			return e;
	return NULL;
}