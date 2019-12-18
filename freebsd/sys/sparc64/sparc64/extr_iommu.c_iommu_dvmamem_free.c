#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iommu_state {int dummy; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_4__ {struct iommu_state* dt_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IOMMU ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_dvma_vfree (struct iommu_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc64_dma_free_map (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iommu_dvmamem_free(bus_dma_tag_t dt, void *vaddr, bus_dmamap_t map)
{
	struct iommu_state *is = dt->dt_cookie;

	iommu_dvma_vfree(is, map);
	sparc64_dma_free_map(dt, map);
	free(vaddr, M_IOMMU);
}