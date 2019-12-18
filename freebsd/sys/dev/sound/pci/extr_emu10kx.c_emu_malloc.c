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
typedef  int /*<<< orphan*/  uint32_t ;
struct emu_mem {int /*<<< orphan*/  dmat; TYPE_1__* card; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_2__ {int dbg_level; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  emu_setmap ; 

__attribute__((used)) static void *
emu_malloc(struct emu_mem *mem, uint32_t sz, bus_addr_t * addr,
    bus_dmamap_t *map)
{
	void *dmabuf;
	int error;

	*addr = 0;
	if ((error = bus_dmamem_alloc(mem->dmat, &dmabuf, BUS_DMA_NOWAIT, map))) {
		if (mem->card->dbg_level > 2)
			device_printf(mem->card->dev, "emu_malloc: failed to alloc DMA map: %d\n", error);
		return (NULL);
		}
	if ((error = bus_dmamap_load(mem->dmat, *map, dmabuf, sz, emu_setmap, addr, 0)) || !*addr) {
		if (mem->card->dbg_level > 2)
			device_printf(mem->card->dev, "emu_malloc: failed to load DMA memory: %d\n", error);
		bus_dmamem_free(mem->dmat, dmabuf, *map);
		return (NULL);
		}
	return (dmabuf);
}