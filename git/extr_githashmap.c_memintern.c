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
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct pool_entry {size_t len; void const* data; TYPE_1__ ent; } ;
struct hashmap {int /*<<< orphan*/  tablesize; } ;
typedef  int /*<<< orphan*/  hashmap_cmp_fn ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct pool_entry*,void const*,void const*,size_t) ; 
 int /*<<< orphan*/  hashmap_add (struct hashmap*,struct pool_entry*) ; 
 int /*<<< orphan*/  hashmap_entry_init (struct pool_entry*,int /*<<< orphan*/ ) ; 
 struct pool_entry* hashmap_get (struct hashmap*,struct pool_entry*,void const*) ; 
 int /*<<< orphan*/  hashmap_init (struct hashmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memhash (void const*,size_t) ; 
 scalar_t__ pool_entry_cmp ; 

const void *memintern(const void *data, size_t len)
{
	static struct hashmap map;
	struct pool_entry key, *e;

	/* initialize string pool hashmap */
	if (!map.tablesize)
		hashmap_init(&map, (hashmap_cmp_fn) pool_entry_cmp, NULL, 0);

	/* lookup interned string in pool */
	hashmap_entry_init(&key, memhash(data, len));
	key.len = len;
	e = hashmap_get(&map, &key, data);
	if (!e) {
		/* not found: create it */
		FLEX_ALLOC_MEM(e, data, data, len);
		hashmap_entry_init(e, key.ent.hash);
		e->len = len;
		hashmap_add(&map, e);
	}
	return e->data;
}