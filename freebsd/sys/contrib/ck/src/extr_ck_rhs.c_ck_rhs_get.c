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
struct ck_rhs_map {unsigned int* generation; int /*<<< orphan*/  (* probe_func ) (struct ck_rhs*,struct ck_rhs_map*,unsigned long*,long*,unsigned long,void const*,void const**,unsigned int,int /*<<< orphan*/ ) ;} ;
struct ck_rhs {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 void* CK_CC_DECONST_PTR (void const*) ; 
 unsigned long CK_RHS_G_MASK ; 
 int /*<<< orphan*/  CK_RHS_PROBE_NO_RH ; 
 int /*<<< orphan*/  ck_pr_fence_load () ; 
 struct ck_rhs_map* ck_pr_load_ptr (int /*<<< orphan*/ *) ; 
 unsigned int ck_pr_load_uint (unsigned int*) ; 
 unsigned int ck_rhs_map_bound_get (struct ck_rhs_map*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ck_rhs*,struct ck_rhs_map*,unsigned long*,long*,unsigned long,void const*,void const**,unsigned int,int /*<<< orphan*/ ) ; 

void *
ck_rhs_get(struct ck_rhs *hs,
    unsigned long h,
    const void *key)
{
	long first;
	const void *object;
	struct ck_rhs_map *map;
	unsigned long n_probes;
	unsigned int g, g_p, probe;
	unsigned int *generation;

	do {
		map = ck_pr_load_ptr(&hs->map);
		generation = &map->generation[h & CK_RHS_G_MASK];
		g = ck_pr_load_uint(generation);
		probe  = ck_rhs_map_bound_get(map, h);
		ck_pr_fence_load();

		first = -1;
		map->probe_func(hs, map, &n_probes, &first, h, key, &object, probe, CK_RHS_PROBE_NO_RH);

		ck_pr_fence_load();
		g_p = ck_pr_load_uint(generation);
	} while (g != g_p);

	return CK_CC_DECONST_PTR(object);
}