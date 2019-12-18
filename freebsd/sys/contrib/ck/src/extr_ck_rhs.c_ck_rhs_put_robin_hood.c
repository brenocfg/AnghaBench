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
struct ck_rhs_map {long (* probe_func ) (struct ck_rhs*,struct ck_rhs_map*,unsigned long*,long*,unsigned long,void*,void const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int capacity; int /*<<< orphan*/ * generation; int /*<<< orphan*/  probe_limit; } ;
struct ck_rhs_entry_desc {unsigned long probes; int in_rh; } ;
struct ck_rhs {int mode; struct ck_rhs_map* map; } ;

/* Variables and functions */
 void* CK_CC_DECONST_PTR (void const*) ; 
 unsigned long CK_RHS_G_MASK ; 
 int CK_RHS_MAX_RH ; 
 int CK_RHS_MODE_OBJECT ; 
 int /*<<< orphan*/  CK_RHS_PROBE_NO_RH ; 
 int /*<<< orphan*/  CK_RHS_PROBE_ROBIN_HOOD ; 
 void* CK_RHS_VMA (void*) ; 
 int /*<<< orphan*/  ck_pr_fence_atomic_store () ; 
 int /*<<< orphan*/  ck_pr_inc_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  ck_rhs_add_wanted (struct ck_rhs*,long,long,unsigned long) ; 
 struct ck_rhs_entry_desc* ck_rhs_desc (struct ck_rhs_map*,long) ; 
 void const* ck_rhs_entry (struct ck_rhs_map*,long) ; 
 int /*<<< orphan*/  ck_rhs_entry_addr (struct ck_rhs_map*,long) ; 
 unsigned long ck_rhs_get_first_offset (struct ck_rhs_map*,long,unsigned long) ; 
 int ck_rhs_grow (struct ck_rhs*,int) ; 
 int /*<<< orphan*/  ck_rhs_map_bound_set (struct ck_rhs_map*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ck_rhs_set_probes (struct ck_rhs_map*,long,unsigned long) ; 
 int /*<<< orphan*/  ck_rhs_set_rh (struct ck_rhs_map*,long) ; 
 int /*<<< orphan*/  ck_rhs_unset_rh (struct ck_rhs_map*,long) ; 
 long stub1 (struct ck_rhs*,struct ck_rhs_map*,unsigned long*,long*,unsigned long,void*,void const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ck_rhs_put_robin_hood(struct ck_rhs *hs,
    long orig_slot, struct ck_rhs_entry_desc *desc)
{
	long slot, first;
	const void *object, *insert;
	unsigned long n_probes;
	struct ck_rhs_map *map;
	unsigned long h = 0;
	long prev;
	void *key;
	long prevs[CK_RHS_MAX_RH];
	unsigned int prevs_nb = 0;
	unsigned int i;

	map = hs->map;
	first = orig_slot;
	n_probes = desc->probes;
restart:
	key = CK_CC_DECONST_PTR(ck_rhs_entry(map, first));
	insert = key;
#ifdef CK_RHS_PP
	if (hs->mode & CK_RHS_MODE_OBJECT)
	    key = CK_RHS_VMA(key);
#endif
	orig_slot = first;
	ck_rhs_set_rh(map, orig_slot);

	slot = map->probe_func(hs, map, &n_probes, &first, h, key, &object,
	    map->probe_limit, prevs_nb == CK_RHS_MAX_RH ?
	    CK_RHS_PROBE_NO_RH : CK_RHS_PROBE_ROBIN_HOOD);

	if (slot == -1 && first == -1) {
		if (ck_rhs_grow(hs, map->capacity << 1) == false) {
			desc->in_rh = false;

			for (i = 0; i < prevs_nb; i++)
				ck_rhs_unset_rh(map, prevs[i]);

			return -1;
		}

		return 1;
	}

	if (first != -1) {
		desc = ck_rhs_desc(map, first);
		int old_probes = desc->probes;

		desc->probes = n_probes;
		h = ck_rhs_get_first_offset(map, first, n_probes);
		ck_rhs_map_bound_set(map, h, n_probes);
		prev = orig_slot;
		prevs[prevs_nb++] = prev;
		n_probes = old_probes;
		goto restart;
	} else {
		/* An empty slot was found. */
		h =  ck_rhs_get_first_offset(map, slot, n_probes);
		ck_rhs_map_bound_set(map, h, n_probes);
		ck_pr_store_ptr(ck_rhs_entry_addr(map, slot), insert);
		ck_pr_inc_uint(&map->generation[h & CK_RHS_G_MASK]);
		ck_pr_fence_atomic_store();
		ck_rhs_set_probes(map, slot, n_probes);
		desc->in_rh = 0;
		ck_rhs_add_wanted(hs, slot, orig_slot, h);
	}
	while (prevs_nb > 0) {
		prev = prevs[--prevs_nb];
		ck_pr_store_ptr(ck_rhs_entry_addr(map, orig_slot),
		    ck_rhs_entry(map, prev));
		h = ck_rhs_get_first_offset(map, orig_slot,
		    desc->probes);
		ck_rhs_add_wanted(hs, orig_slot, prev, h);
		ck_pr_inc_uint(&map->generation[h & CK_RHS_G_MASK]);
		ck_pr_fence_atomic_store();
		orig_slot = prev;
		desc->in_rh = false;
		desc = ck_rhs_desc(map, orig_slot);
	}
	return 0;
}