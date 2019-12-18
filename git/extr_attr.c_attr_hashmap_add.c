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
struct attr_hash_entry {char const* key; size_t keylen; int /*<<< orphan*/  ent; void* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_hashmap_init (struct attr_hashmap*) ; 
 int /*<<< orphan*/  hashmap_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memhash (char const*,size_t) ; 
 struct attr_hash_entry* xmalloc (int) ; 

__attribute__((used)) static void attr_hashmap_add(struct attr_hashmap *map,
			     const char *key, size_t keylen,
			     void *value)
{
	struct attr_hash_entry *e;

	if (!map->map.tablesize)
		attr_hashmap_init(map);

	e = xmalloc(sizeof(struct attr_hash_entry));
	hashmap_entry_init(&e->ent, memhash(key, keylen));
	e->key = key;
	e->keylen = keylen;
	e->value = value;

	hashmap_add(&map->map, &e->ent);
}