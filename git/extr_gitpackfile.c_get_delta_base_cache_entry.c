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
struct packed_git {int dummy; } ;
struct hashmap_entry {int dummy; } ;
struct delta_base_cache_key {int /*<<< orphan*/  base_offset; struct packed_git* p; } ;
struct delta_base_cache_entry {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/  cmpfn; } ;

/* Variables and functions */
 TYPE_1__ delta_base_cache ; 
 int /*<<< orphan*/  hashmap_entry_init (struct hashmap_entry*,int /*<<< orphan*/ ) ; 
 struct delta_base_cache_entry* hashmap_get (TYPE_1__*,struct hashmap_entry*,struct delta_base_cache_key*) ; 
 int /*<<< orphan*/  pack_entry_hash (struct packed_git*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct delta_base_cache_entry *
get_delta_base_cache_entry(struct packed_git *p, off_t base_offset)
{
	struct hashmap_entry entry;
	struct delta_base_cache_key key;

	if (!delta_base_cache.cmpfn)
		return NULL;

	hashmap_entry_init(&entry, pack_entry_hash(p, base_offset));
	key.p = p;
	key.base_offset = base_offset;
	return hashmap_get(&delta_base_cache, &entry, &key);
}