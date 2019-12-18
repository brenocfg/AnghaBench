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
struct ck_rhs_map {long (* probe_func ) (struct ck_rhs*,struct ck_rhs_map*,unsigned long*,long*,unsigned long,void const*,void const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * generation; } ;
struct ck_rhs_entry_desc {int in_rh; unsigned long probes; } ;
struct ck_rhs {int /*<<< orphan*/  mode; struct ck_rhs_map* map; } ;

/* Variables and functions */
 void* CK_CC_DECONST_PTR (void const*) ; 
 scalar_t__ CK_CC_UNLIKELY (int) ; 
 unsigned long CK_RHS_G_MASK ; 
 int /*<<< orphan*/  CK_RHS_PROBE ; 
 int /*<<< orphan*/  ck_pr_fence_atomic_store () ; 
 int /*<<< orphan*/  ck_pr_inc_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  ck_rhs_add_wanted (struct ck_rhs*,long,int,unsigned long) ; 
 struct ck_rhs_entry_desc* ck_rhs_desc (struct ck_rhs_map*,long) ; 
 int /*<<< orphan*/  ck_rhs_do_backward_shift_delete (struct ck_rhs*,long) ; 
 int /*<<< orphan*/  ck_rhs_entry_addr (struct ck_rhs_map*,long) ; 
 int /*<<< orphan*/  ck_rhs_map_bound_get (struct ck_rhs_map*,unsigned long) ; 
 void* ck_rhs_marshal (int /*<<< orphan*/ ,void const*,unsigned long) ; 
 int ck_rhs_put_robin_hood (struct ck_rhs*,long,struct ck_rhs_entry_desc*) ; 
 int /*<<< orphan*/  ck_rhs_set_probes (struct ck_rhs_map*,long,unsigned long) ; 
 long stub1 (struct ck_rhs*,struct ck_rhs_map*,unsigned long*,long*,unsigned long,void const*,void const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ck_rhs_fas(struct ck_rhs *hs,
    unsigned long h,
    const void *key,
    void **previous)
{
	long slot, first;
	const void *object;
	const void *insert;
	unsigned long n_probes;
	struct ck_rhs_map *map = hs->map;
	struct ck_rhs_entry_desc *desc, *desc2;

	*previous = NULL;
restart:
	slot = map->probe_func(hs, map, &n_probes, &first, h, key, &object,
	    ck_rhs_map_bound_get(map, h), CK_RHS_PROBE);

	/* Replacement semantics presume existence. */
	if (object == NULL)
		return false;

	insert = ck_rhs_marshal(hs->mode, key, h);

	if (first != -1) {
		int ret;

		desc = ck_rhs_desc(map, slot);
		desc2 = ck_rhs_desc(map, first);
		desc->in_rh = true;
		ret = ck_rhs_put_robin_hood(hs, first, desc2);
		desc->in_rh = false;
		if (CK_CC_UNLIKELY(ret == 1))
			goto restart;
		else if (CK_CC_UNLIKELY(ret != 0))
			return false;
		ck_pr_store_ptr(ck_rhs_entry_addr(map, first), insert);
		ck_pr_inc_uint(&map->generation[h & CK_RHS_G_MASK]);
		ck_pr_fence_atomic_store();
		desc2->probes = n_probes;
		ck_rhs_add_wanted(hs, first, -1, h);
		ck_rhs_do_backward_shift_delete(hs, slot);
	} else {
		ck_pr_store_ptr(ck_rhs_entry_addr(map, slot), insert);
		ck_rhs_set_probes(map, slot, n_probes);
	}
	*previous = CK_CC_DECONST_PTR(object);
	return true;
}