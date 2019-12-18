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
struct bus_dmamap_dmar {int locked; int /*<<< orphan*/  cansleep; } ;
struct TYPE_2__ {int /*<<< orphan*/  lockfuncarg; int /*<<< orphan*/  (* lockfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct bus_dma_tag_dmar {int /*<<< orphan*/ * segments; TYPE_1__ common; } ;
typedef  scalar_t__ bus_dmamap_t ;
typedef  scalar_t__ bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_LOCK ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bus_dma_segment_t *
dmar_bus_dmamap_complete(bus_dma_tag_t dmat, bus_dmamap_t map1,
    bus_dma_segment_t *segs, int nsegs, int error)
{
	struct bus_dma_tag_dmar *tag;
	struct bus_dmamap_dmar *map;

	tag = (struct bus_dma_tag_dmar *)dmat;
	map = (struct bus_dmamap_dmar *)map1;

	if (!map->locked) {
		KASSERT(map->cansleep,
		    ("map not locked and not sleepable context %p", map));

		/*
		 * We are called from the delayed context.  Relock the
		 * driver.
		 */
		(tag->common.lockfunc)(tag->common.lockfuncarg, BUS_DMA_LOCK);
		map->locked = true;
	}

	if (segs == NULL)
		segs = tag->segments;
	return (segs);
}