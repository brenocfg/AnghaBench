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
struct ck_hs_map {unsigned long mask; int /*<<< orphan*/ * entries; } ;
struct ck_hs {int mode; int (* compare ) (void const*,void const*) ;} ;
typedef  enum ck_hs_probe_behavior { ____Placeholder_ck_hs_probe_behavior } ck_hs_probe_behavior ;

/* Variables and functions */
 void const* CK_HS_EMPTY ; 
 unsigned long CK_HS_KEY_MASK ; 
 int CK_HS_MODE_OBJECT ; 
 int CK_HS_PROBE_INSERT ; 
 unsigned long CK_HS_PROBE_L1 ; 
 int CK_HS_PROBE_TOMBSTONE ; 
 void const* CK_HS_TOMBSTONE ; 
 void* CK_HS_VMA (void const*) ; 
 int CK_MD_CACHELINE ; 
 uintptr_t CK_MD_VMA_BITS ; 
 unsigned long ck_hs_map_bound_get (struct ck_hs_map*,unsigned long) ; 
 unsigned long ck_hs_map_probe_next (struct ck_hs_map*,unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 void* ck_pr_load_ptr (void const**) ; 
 int stub1 (void const*,void const*) ; 

__attribute__((used)) static const void **
ck_hs_map_probe(struct ck_hs *hs,
    struct ck_hs_map *map,
    unsigned long *n_probes,
    const void ***priority,
    unsigned long h,
    const void *key,
    const void **object,
    unsigned long probe_limit,
    enum ck_hs_probe_behavior behavior)
{
	const void **bucket, **cursor, *k, *compare;
	const void **pr = NULL;
	unsigned long offset, j, i, probes, opl;

#ifdef CK_HS_PP
	/* If we are storing object pointers, then we may leverage pointer packing. */
	unsigned long hv = 0;

	if (hs->mode & CK_HS_MODE_OBJECT) {
		hv = (h >> 25) & CK_HS_KEY_MASK;
		compare = CK_HS_VMA(key);
	} else {
		compare = key;
	}
#else
	compare = key;
#endif

	offset = h & map->mask;
	*object = NULL;
	i = probes = 0;

	opl = probe_limit;
	if (behavior == CK_HS_PROBE_INSERT)
		probe_limit = ck_hs_map_bound_get(map, h);

	for (;;) {
		bucket = (const void **)((uintptr_t)&map->entries[offset] & ~(CK_MD_CACHELINE - 1));

		for (j = 0; j < CK_HS_PROBE_L1; j++) {
			cursor = bucket + ((j + offset) & (CK_HS_PROBE_L1 - 1));

			if (probes++ == probe_limit) {
				if (probe_limit == opl || pr != NULL) {
					k = CK_HS_EMPTY;
					goto leave;
				}

				/*
				 * If no eligible slot has been found yet, continue probe
				 * sequence with original probe limit.
				 */
				probe_limit = opl;
			}

			k = ck_pr_load_ptr(cursor);
			if (k == CK_HS_EMPTY)
				goto leave;

			if (k == CK_HS_TOMBSTONE) {
				if (pr == NULL) {
					pr = cursor;
					*n_probes = probes;

					if (behavior == CK_HS_PROBE_TOMBSTONE) {
						k = CK_HS_EMPTY;
						goto leave;
					}
				}

				continue;
			}

#ifdef CK_HS_PP
			if (hs->mode & CK_HS_MODE_OBJECT) {
				if (((uintptr_t)k >> CK_MD_VMA_BITS) != hv)
					continue;

				k = CK_HS_VMA(k);
			}
#endif

			if (k == compare)
				goto leave;

			if (hs->compare == NULL)
				continue;

			if (hs->compare(k, key) == true)
				goto leave;
		}

		offset = ck_hs_map_probe_next(map, offset, h, i++, probes);
	}

leave:
	if (probes > probe_limit) {
		cursor = NULL;
	} else {
		*object = k;
	}

	if (pr == NULL)
		*n_probes = probes;

	*priority = pr;
	return cursor;
}