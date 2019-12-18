#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct pool_entry {size_t len; void const* data; TYPE_1__ ent; } ;
struct hashmap {int /*<<< orphan*/  tablesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct pool_entry*,void const*,void const*,size_t) ; 
 int /*<<< orphan*/  ent ; 
 int /*<<< orphan*/  hashmap_add (struct hashmap*,TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_entry_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct pool_entry* hashmap_get_entry (struct hashmap*,struct pool_entry*,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  hashmap_init (struct hashmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memhash (void const*,size_t) ; 
 int /*<<< orphan*/  pool_entry_cmp ; 

const void *memintern(const void *data, size_t len)
{
	static struct hashmap map;
	struct pool_entry key, *e;

	/* initialize string pool hashmap */
	if (!map.tablesize)
		hashmap_init(&map, pool_entry_cmp, NULL, 0);

	/* lookup interned string in pool */
	hashmap_entry_init(&key.ent, memhash(data, len));
	key.len = len;
	e = hashmap_get_entry(&map, &key, ent, data);
	if (!e) {
		/* not found: create it */
		FLEX_ALLOC_MEM(e, data, data, len);
		hashmap_entry_init(&e->ent, key.ent.hash);
		e->len = len;
		hashmap_add(&map, &e->ent);
	}
	return e->data;
}