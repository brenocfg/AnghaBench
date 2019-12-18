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
struct hashmap_entry {int dummy; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_add (struct hashmap*,struct hashmap_entry*) ; 
 struct hashmap_entry* hashmap_remove (struct hashmap*,struct hashmap_entry*,int /*<<< orphan*/ *) ; 

struct hashmap_entry *hashmap_put(struct hashmap *map,
				struct hashmap_entry *entry)
{
	struct hashmap_entry *old = hashmap_remove(map, entry, NULL);
	hashmap_add(map, entry);
	return old;
}