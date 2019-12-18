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
struct oidmap_entry {int /*<<< orphan*/  internal_entry; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmpfn; } ;
struct oidmap {TYPE_1__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* hashmap_put (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidhash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidmap_init (struct oidmap*,int /*<<< orphan*/ ) ; 

void *oidmap_put(struct oidmap *map, void *entry)
{
	struct oidmap_entry *to_put = entry;

	if (!map->map.cmpfn)
		oidmap_init(map, 0);

	hashmap_entry_init(&to_put->internal_entry, oidhash(&to_put->oid));
	return hashmap_put(&map->map, &to_put->internal_entry);
}