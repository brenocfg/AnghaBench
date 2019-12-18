#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iommu_state {int /*<<< orphan*/  is_bushandle; int /*<<< orphan*/  is_bustag; } ;
typedef  int bus_dmasync_op_t ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
struct TYPE_6__ {struct iommu_state* dt_cookie; } ;
struct TYPE_5__ {int dm_flags; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int DMF_LOADED ; 
 int /*<<< orphan*/  PSR_DMA_WRITE_SYNC ; 
 int /*<<< orphan*/  Sync ; 
 int /*<<< orphan*/  bus_space_read_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  membar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sabre_dmamap_sync(bus_dma_tag_t dt, bus_dmamap_t map, bus_dmasync_op_t op)
{
	struct iommu_state *is = dt->dt_cookie;

	if ((map->dm_flags & DMF_LOADED) == 0)
		return;

	if ((op & BUS_DMASYNC_POSTREAD) != 0)
		(void)bus_space_read_8(is->is_bustag, is->is_bushandle,
		    PSR_DMA_WRITE_SYNC);

	if ((op & BUS_DMASYNC_PREWRITE) != 0)
		membar(Sync);
}