#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bounce_page {int dummy; } ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
struct TYPE_7__ {int /*<<< orphan*/  iommu_cookie; scalar_t__ iommu; } ;
struct TYPE_6__ {int /*<<< orphan*/  bpages; scalar_t__ nsegs; int /*<<< orphan*/  segments; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_UNMAP (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct bounce_page* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_bounce_page (TYPE_2__*,struct bounce_page*) ; 
 int /*<<< orphan*/  links ; 

void
bus_dmamap_unload(bus_dma_tag_t dmat, bus_dmamap_t map)
{
	struct bounce_page *bpage;

	if (dmat->iommu) {
		IOMMU_UNMAP(dmat->iommu, map->segments, map->nsegs, dmat->iommu_cookie);
		map->nsegs = 0;
	}

	while ((bpage = STAILQ_FIRST(&map->bpages)) != NULL) {
		STAILQ_REMOVE_HEAD(&map->bpages, links);
		free_bounce_page(dmat, bpage);
	}
}