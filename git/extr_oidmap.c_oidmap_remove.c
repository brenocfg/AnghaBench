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
struct TYPE_2__ {int /*<<< orphan*/  cmpfn; } ;
struct oidmap {TYPE_1__ map; } ;
struct object_id {int dummy; } ;
struct hashmap_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_entry_init (struct hashmap_entry*,int /*<<< orphan*/ ) ; 
 void* hashmap_remove (TYPE_1__*,struct hashmap_entry*,struct object_id const*) ; 
 int /*<<< orphan*/  oidhash (struct object_id const*) ; 
 int /*<<< orphan*/  oidmap_init (struct oidmap*,int /*<<< orphan*/ ) ; 

void *oidmap_remove(struct oidmap *map, const struct object_id *key)
{
	struct hashmap_entry entry;

	if (!map->map.cmpfn)
		oidmap_init(map, 0);

	hashmap_entry_init(&entry, oidhash(key));
	return hashmap_remove(&map->map, &entry, key);
}