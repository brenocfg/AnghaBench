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
struct TYPE_2__ {int /*<<< orphan*/  tablesize; } ;
struct attr_hashmap {TYPE_1__ map; } ;
struct attr_hash_entry {char const* key; size_t keylen; void* value; int /*<<< orphan*/  ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_hashmap_init (struct attr_hashmap*) ; 
 int /*<<< orphan*/  ent ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct attr_hash_entry* hashmap_get_entry (TYPE_1__*,struct attr_hash_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memhash (char const*,size_t) ; 

__attribute__((used)) static void *attr_hashmap_get(struct attr_hashmap *map,
			      const char *key, size_t keylen)
{
	struct attr_hash_entry k;
	struct attr_hash_entry *e;

	if (!map->map.tablesize)
		attr_hashmap_init(map);

	hashmap_entry_init(&k.ent, memhash(key, keylen));
	k.key = key;
	k.keylen = keylen;
	e = hashmap_get_entry(&map->map, &k, ent, NULL);

	return e ? e->value : NULL;
}