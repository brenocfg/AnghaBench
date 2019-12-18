#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct phys_addr {int dummy; } ;
struct _oce_dmamap_paddr_table {int max_entries; scalar_t__ num_entries; struct phys_addr* paddrs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  map; int /*<<< orphan*/  tag; } ;
struct TYPE_5__ {int item_size; int num_items; TYPE_1__ dma; } ;
typedef  TYPE_2__ oce_ring_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct _oce_dmamap_paddr_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_dma_map_ring ; 

uint32_t
oce_page_list(oce_ring_buffer_t *ring, struct phys_addr *pa_list)
{
	struct _oce_dmamap_paddr_table dpt;

	dpt.max_entries = 8;
	dpt.num_entries = 0;
	dpt.paddrs = pa_list;

	bus_dmamap_load(ring->dma.tag,
			ring->dma.map,
			ring->dma.ptr,
			ring->item_size * ring->num_items,
			oce_dma_map_ring, &dpt, BUS_DMA_NOWAIT);

	return dpt.num_entries;
}