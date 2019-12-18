#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iommu_state {int dummy; } ;
typedef  scalar_t__ bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
struct TYPE_3__ {int dm_flags; } ;

/* Variables and functions */
 int DMF_COHERENT ; 
 scalar_t__ IOMMU_HAS_SB (struct iommu_state*) ; 
 scalar_t__ IOMMU_STREAM_THRESH ; 

__attribute__((used)) static __inline int
iommu_use_streaming(struct iommu_state *is, bus_dmamap_t map, bus_size_t size)
{

	return (size >= IOMMU_STREAM_THRESH && IOMMU_HAS_SB(is) &&
	    (map->dm_flags & DMF_COHERENT) == 0);
}