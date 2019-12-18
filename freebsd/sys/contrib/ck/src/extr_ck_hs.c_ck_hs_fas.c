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
struct ck_hs_map {int dummy; } ;
struct ck_hs {int /*<<< orphan*/  mode; struct ck_hs_map* map; } ;

/* Variables and functions */
 void* CK_CC_DECONST_PTR (void const*) ; 
 int /*<<< orphan*/  CK_HS_PROBE ; 
 void const* CK_HS_TOMBSTONE ; 
 int /*<<< orphan*/  ck_hs_map_bound_get (struct ck_hs_map*,unsigned long) ; 
 void** ck_hs_map_probe (struct ck_hs*,struct ck_hs_map*,unsigned long*,void const***,unsigned long,void const*,void const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_hs_map_signal (struct ck_hs_map*,unsigned long) ; 
 void* ck_hs_marshal (int /*<<< orphan*/ ,void const*,unsigned long) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (void const**,void const*) ; 

bool
ck_hs_fas(struct ck_hs *hs,
    unsigned long h,
    const void *key,
    void **previous)
{
	const void **slot, **first, *object, *insert;
	struct ck_hs_map *map = hs->map;
	unsigned long n_probes;

	*previous = NULL;
	slot = ck_hs_map_probe(hs, map, &n_probes, &first, h, key, &object,
	    ck_hs_map_bound_get(map, h), CK_HS_PROBE);

	/* Replacement semantics presume existence. */
	if (object == NULL)
		return false;

	insert = ck_hs_marshal(hs->mode, key, h);

	if (first != NULL) {
		ck_pr_store_ptr(first, insert);
		ck_hs_map_signal(map, h);
		ck_pr_store_ptr(slot, CK_HS_TOMBSTONE);
	} else {
		ck_pr_store_ptr(slot, insert);
	}

	*previous = CK_CC_DECONST_PTR(object);
	return true;
}