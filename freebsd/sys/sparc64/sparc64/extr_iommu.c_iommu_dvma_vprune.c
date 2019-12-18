#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iommu_state {int dummy; } ;
struct bus_dmamap_res {scalar_t__ dr_used; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
struct TYPE_5__ {int /*<<< orphan*/  dm_reslist; } ;

/* Variables and functions */
 scalar_t__ BDR_SIZE (struct bus_dmamap_res*) ; 
 int /*<<< orphan*/  IS_LOCK_ASSERT (struct iommu_state*) ; 
 scalar_t__ SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct bus_dmamap_res* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct bus_dmamap_res* SLIST_NEXT (struct bus_dmamap_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_link ; 
 int /*<<< orphan*/  iommu_dvma_vfree_res (TYPE_1__*,struct bus_dmamap_res*) ; 
 int /*<<< orphan*/  iommu_map_remq (struct iommu_state*,TYPE_1__*) ; 

__attribute__((used)) static bus_size_t
iommu_dvma_vprune(struct iommu_state *is, bus_dmamap_t map)
{
	struct bus_dmamap_res *r, *n;
	bus_size_t freed = 0;

	IS_LOCK_ASSERT(is);
	for (r = SLIST_FIRST(&map->dm_reslist); r != NULL; r = n) {
		n = SLIST_NEXT(r, dr_link);
		if (r->dr_used == 0) {
			freed += BDR_SIZE(r);
			iommu_dvma_vfree_res(map, r);
		}
	}
	if (SLIST_EMPTY(&map->dm_reslist))
		iommu_map_remq(is, map);
	return (freed);
}