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
struct ck_rhs_map {long (* probe_func ) (struct ck_rhs*,struct ck_rhs_map*,unsigned long*,long*,unsigned long,void const*,void const**,int /*<<< orphan*/ ,int) ;int capacity; scalar_t__ n_entries; scalar_t__ max_entries; int /*<<< orphan*/  probe_limit; } ;
struct ck_rhs_entry_desc {unsigned long probes; } ;
struct ck_rhs {int /*<<< orphan*/  mode; struct ck_rhs_map* map; } ;
typedef  enum ck_rhs_probe_behavior { ____Placeholder_ck_rhs_probe_behavior } ck_rhs_probe_behavior ;

/* Variables and functions */
 scalar_t__ CK_CC_UNLIKELY (int) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  ck_rhs_add_wanted (struct ck_rhs*,long,int,unsigned long) ; 
 struct ck_rhs_entry_desc* ck_rhs_desc (struct ck_rhs_map*,long) ; 
 int /*<<< orphan*/  ck_rhs_entry_addr (struct ck_rhs_map*,long) ; 
 int ck_rhs_grow (struct ck_rhs*,int) ; 
 int /*<<< orphan*/  ck_rhs_map_bound_set (struct ck_rhs_map*,unsigned long,unsigned long) ; 
 void* ck_rhs_marshal (int /*<<< orphan*/ ,void const*,unsigned long) ; 
 int ck_rhs_put_robin_hood (struct ck_rhs*,long,struct ck_rhs_entry_desc*) ; 
 int /*<<< orphan*/  ck_rhs_set_probes (struct ck_rhs_map*,long,unsigned long) ; 
 long stub1 (struct ck_rhs*,struct ck_rhs_map*,unsigned long*,long*,unsigned long,void const*,void const**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
ck_rhs_put_internal(struct ck_rhs *hs,
    unsigned long h,
    const void *key,
    enum ck_rhs_probe_behavior behavior)
{
	long slot, first;
	const void *object;
	const void *insert;
	unsigned long n_probes;
	struct ck_rhs_map *map;

restart:
	map = hs->map;

	slot = map->probe_func(hs, map, &n_probes, &first, h, key, &object,
	    map->probe_limit, behavior);

	if (slot == -1 && first == -1) {
		if (ck_rhs_grow(hs, map->capacity << 1) == false)
			return false;

		goto restart;
	}

	/* Fail operation if a match was found. */
	if (object != NULL)
		return false;

	ck_rhs_map_bound_set(map, h, n_probes);
	insert = ck_rhs_marshal(hs->mode, key, h);

	if (first != -1) {
		struct ck_rhs_entry_desc *desc = ck_rhs_desc(map, first);
		int ret = ck_rhs_put_robin_hood(hs, first, desc);
		if (CK_CC_UNLIKELY(ret == 1))
			return ck_rhs_put_internal(hs, h, key, behavior);
		else if (CK_CC_UNLIKELY(ret == -1))
			return false;
		/* Insert key into first bucket in probe sequence. */
		ck_pr_store_ptr(ck_rhs_entry_addr(map, first), insert);
		desc->probes = n_probes;
		ck_rhs_add_wanted(hs, first, -1, h);
	} else {
		/* An empty slot was found. */
		ck_pr_store_ptr(ck_rhs_entry_addr(map, slot), insert);
		ck_rhs_set_probes(map, slot, n_probes);
		ck_rhs_add_wanted(hs, slot, -1, h);
	}

	map->n_entries++;
	if ((map->n_entries ) > map->max_entries)
		ck_rhs_grow(hs, map->capacity << 1);
	return true;
}