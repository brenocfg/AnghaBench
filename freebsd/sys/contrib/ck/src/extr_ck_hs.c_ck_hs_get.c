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
struct ck_hs_map {unsigned int* generation; } ;
struct ck_hs {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 void* CK_CC_DECONST_PTR (void const*) ; 
 unsigned long CK_HS_G_MASK ; 
 int /*<<< orphan*/  CK_HS_PROBE ; 
 unsigned int ck_hs_map_bound_get (struct ck_hs_map*,unsigned long) ; 
 int /*<<< orphan*/  ck_hs_map_probe (struct ck_hs*,struct ck_hs_map*,unsigned long*,void const***,unsigned long,void const*,void const**,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_pr_fence_load () ; 
 struct ck_hs_map* ck_pr_load_ptr (int /*<<< orphan*/ *) ; 
 unsigned int ck_pr_load_uint (unsigned int*) ; 

void *
ck_hs_get(struct ck_hs *hs,
    unsigned long h,
    const void *key)
{
	const void **first, *object;
	struct ck_hs_map *map;
	unsigned long n_probes;
	unsigned int g, g_p, probe;
	unsigned int *generation;

	do {
		map = ck_pr_load_ptr(&hs->map);
		generation = &map->generation[h & CK_HS_G_MASK];
		g = ck_pr_load_uint(generation);
		probe  = ck_hs_map_bound_get(map, h);
		ck_pr_fence_load();

		ck_hs_map_probe(hs, map, &n_probes, &first, h, key, &object, probe, CK_HS_PROBE);

		ck_pr_fence_load();
		g_p = ck_pr_load_uint(generation);
	} while (g != g_p);

	return CK_CC_DECONST_PTR(object);
}