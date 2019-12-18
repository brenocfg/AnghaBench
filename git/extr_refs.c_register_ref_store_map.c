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
struct ref_store_hash_entry {int /*<<< orphan*/  ent; } ;
struct ref_store {int dummy; } ;
struct hashmap {int /*<<< orphan*/  tablesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*,char const*) ; 
 struct ref_store_hash_entry* alloc_ref_store_hash_entry (char const*,struct ref_store*) ; 
 int /*<<< orphan*/  hashmap_init (struct hashmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hashmap_put (struct hashmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_store_hash_cmp ; 

__attribute__((used)) static void register_ref_store_map(struct hashmap *map,
				   const char *type,
				   struct ref_store *refs,
				   const char *name)
{
	struct ref_store_hash_entry *entry;

	if (!map->tablesize)
		hashmap_init(map, ref_store_hash_cmp, NULL, 0);

	entry = alloc_ref_store_hash_entry(name, refs);
	if (hashmap_put(map, &entry->ent))
		BUG("%s ref_store '%s' initialized twice", type, name);
}