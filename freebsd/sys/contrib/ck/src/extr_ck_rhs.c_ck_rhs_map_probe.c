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
struct TYPE_2__ {struct ck_rhs_entry_desc* descs; } ;
struct ck_rhs_map {unsigned long mask; TYPE_1__ entries; } ;
struct ck_rhs_entry_desc {int in_rh; unsigned long probes; int /*<<< orphan*/  entry; } ;
struct ck_rhs {int mode; int (* compare ) (void const*,void const*) ;} ;
typedef  enum ck_rhs_probe_behavior { ____Placeholder_ck_rhs_probe_behavior } ck_rhs_probe_behavior ;

/* Variables and functions */
 uintptr_t CK_MD_VMA_BITS ; 
 void const* CK_RHS_EMPTY ; 
 unsigned long CK_RHS_KEY_MASK ; 
 int CK_RHS_MODE_OBJECT ; 
 int CK_RHS_PROBE_INSERT ; 
 int CK_RHS_PROBE_NO_RH ; 
 int CK_RHS_PROBE_RH ; 
 int CK_RHS_PROBE_ROBIN_HOOD ; 
 void* CK_RHS_VMA (void const*) ; 
 void* ck_pr_load_ptr (int /*<<< orphan*/ *) ; 
 unsigned long ck_rhs_map_bound_get (struct ck_rhs_map*,unsigned long) ; 
 unsigned long ck_rhs_map_probe_next (struct ck_rhs_map*,unsigned long,unsigned long) ; 
 int stub1 (void const*,void const*) ; 

__attribute__((used)) static long
ck_rhs_map_probe(struct ck_rhs *hs,
    struct ck_rhs_map *map,
    unsigned long *n_probes,
    long *priority,
    unsigned long h,
    const void *key,
    const void **object,
    unsigned long probe_limit,
    enum ck_rhs_probe_behavior behavior)
{
	const void *k;
	const void *compare;
	long pr = -1;
	unsigned long offset, probes, opl;

#ifdef CK_RHS_PP
	/* If we are storing object pointers, then we may leverage pointer packing. */
	unsigned long hv = 0;

	if (hs->mode & CK_RHS_MODE_OBJECT) {
		hv = (h >> 25) & CK_RHS_KEY_MASK;
		compare = CK_RHS_VMA(key);
	} else {
		compare = key;
	}
#else
	compare = key;
#endif

 	*object = NULL;
	if (behavior != CK_RHS_PROBE_ROBIN_HOOD) {
		probes = 0;
		offset = h & map->mask;
	} else {
		/* Restart from the bucket we were previously in */
		probes = *n_probes;
		offset = ck_rhs_map_probe_next(map, *priority,
		    probes);
	}
	opl = probe_limit;
	if (behavior == CK_RHS_PROBE_INSERT)
		probe_limit = ck_rhs_map_bound_get(map, h);

	for (;;) {
		if (probes++ == probe_limit) {
			if (probe_limit == opl || pr != -1) {
				k = CK_RHS_EMPTY;
				goto leave;
			}
			/*
			 * If no eligible slot has been found yet, continue probe
			 * sequence with original probe limit.
			 */
			probe_limit = opl;
		}
		k = ck_pr_load_ptr(&map->entries.descs[offset].entry);
		if (k == CK_RHS_EMPTY)
			goto leave;
		if ((behavior != CK_RHS_PROBE_NO_RH)) {
			struct ck_rhs_entry_desc *desc = &map->entries.descs[offset];

			if (pr == -1 &&
			    desc->in_rh == false && desc->probes < probes) {
				pr = offset;
				*n_probes = probes;

				if (behavior == CK_RHS_PROBE_RH ||
				    behavior == CK_RHS_PROBE_ROBIN_HOOD) {
					k = CK_RHS_EMPTY;
					goto leave;
				}
			}
		}

		if (behavior != CK_RHS_PROBE_ROBIN_HOOD) {
#ifdef CK_RHS_PP
			if (hs->mode & CK_RHS_MODE_OBJECT) {
				if (((uintptr_t)k >> CK_MD_VMA_BITS) != hv) {
					offset = ck_rhs_map_probe_next(map, offset, probes);
					continue;
				}

				k = CK_RHS_VMA(k);
			}
#endif

			if (k == compare)
				goto leave;

			if (hs->compare == NULL) {
				offset = ck_rhs_map_probe_next(map, offset, probes);
				continue;
			}

			if (hs->compare(k, key) == true)
				goto leave;
		}
		offset = ck_rhs_map_probe_next(map, offset, probes);
	}
leave:
	if (probes > probe_limit) {
		offset = -1;
	} else {
		*object = k;
	}

	if (pr == -1)
		*n_probes = probes;

	*priority = pr;
	return offset;
}