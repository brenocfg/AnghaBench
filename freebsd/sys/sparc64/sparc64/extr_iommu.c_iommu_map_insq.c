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
struct iommu_state {int /*<<< orphan*/  is_maplruq; } ;
typedef  TYPE_1__* bus_dmamap_t ;
struct TYPE_5__ {int dm_onq; int /*<<< orphan*/  dm_reslist; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LOCK_ASSERT (struct iommu_state*) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_maplruq ; 

__attribute__((used)) static __inline void
iommu_map_insq(struct iommu_state *is, bus_dmamap_t map)
{

	IS_LOCK_ASSERT(is);
	if (!SLIST_EMPTY(&map->dm_reslist)) {
		if (map->dm_onq)
			TAILQ_REMOVE(&is->is_maplruq, map, dm_maplruq);
		TAILQ_INSERT_TAIL(&is->is_maplruq, map, dm_maplruq);
		map->dm_onq = 1;
	}
}