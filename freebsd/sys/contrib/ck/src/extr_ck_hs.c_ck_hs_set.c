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
struct ck_hs_map {int capacity; int /*<<< orphan*/  probe_limit; } ;
struct ck_hs {int /*<<< orphan*/  mode; struct ck_hs_map* map; } ;

/* Variables and functions */
 void* CK_CC_DECONST_PTR (void const*) ; 
 int /*<<< orphan*/  CK_HS_PROBE_INSERT ; 
 void const* CK_HS_TOMBSTONE ; 
 int ck_hs_grow (struct ck_hs*,int) ; 
 int /*<<< orphan*/  ck_hs_map_bound_set (struct ck_hs_map*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ck_hs_map_postinsert (struct ck_hs*,struct ck_hs_map*) ; 
 void** ck_hs_map_probe (struct ck_hs*,struct ck_hs_map*,unsigned long*,void const***,unsigned long,void const*,void const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_hs_map_signal (struct ck_hs_map*,unsigned long) ; 
 void* ck_hs_marshal (int /*<<< orphan*/ ,void const*,unsigned long) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (void const**,void const*) ; 

bool
ck_hs_set(struct ck_hs *hs,
    unsigned long h,
    const void *key,
    void **previous)
{
	const void **slot, **first, *object, *insert;
	unsigned long n_probes;
	struct ck_hs_map *map;

	*previous = NULL;

restart:
	map = hs->map;

	slot = ck_hs_map_probe(hs, map, &n_probes, &first, h, key, &object, map->probe_limit, CK_HS_PROBE_INSERT);
	if (slot == NULL && first == NULL) {
		if (ck_hs_grow(hs, map->capacity << 1) == false)
			return false;

		goto restart;
	}

	ck_hs_map_bound_set(map, h, n_probes);
	insert = ck_hs_marshal(hs->mode, key, h);

	if (first != NULL) {
		/* If an earlier bucket was found, then store entry there. */
		ck_pr_store_ptr(first, insert);

		/*
		 * If a duplicate key was found, then delete it after
		 * signaling concurrent probes to restart. Optionally,
		 * it is possible to install tombstone after grace
		 * period if we can guarantee earlier position of
		 * duplicate key.
		 */
		if (object != NULL) {
			ck_hs_map_signal(map, h);
			ck_pr_store_ptr(slot, CK_HS_TOMBSTONE);
		}
	} else {
		/*
		 * If we are storing into same slot, then atomic store is sufficient
		 * for replacement.
		 */
		ck_pr_store_ptr(slot, insert);
	}

	if (object == NULL)
		ck_hs_map_postinsert(hs, map);

	*previous = CK_CC_DECONST_PTR(object);
	return true;
}