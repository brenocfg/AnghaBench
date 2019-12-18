#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iommu_state {int dummy; } ;
typedef  TYPE_1__* bus_dmamap_t ;
struct TYPE_6__ {int /*<<< orphan*/  dm_reslist; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LOCK (struct iommu_state*) ; 
 int /*<<< orphan*/  IS_UNLOCK (struct iommu_state*) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_dvma_vfree_res (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_dvmamap_vunload (struct iommu_state*,TYPE_1__*) ; 
 int /*<<< orphan*/  iommu_map_remq (struct iommu_state*,TYPE_1__*) ; 

__attribute__((used)) static void
iommu_dvma_vfree(struct iommu_state *is, bus_dmamap_t map)
{

	IS_LOCK(is);
	iommu_map_remq(is, map);
	iommu_dvmamap_vunload(is, map);
	IS_UNLOCK(is);
	while (!SLIST_EMPTY(&map->dm_reslist))
		iommu_dvma_vfree_res(map, SLIST_FIRST(&map->dm_reslist));
}