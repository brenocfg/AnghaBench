#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwdma_map_cb ; 
 int /*<<< orphan*/  printf (char*) ; 

void *
fwdma_malloc_size(bus_dma_tag_t dmat, bus_dmamap_t *dmamap,
	bus_size_t size, bus_addr_t *bus_addr, int flag)
{
	void *v_addr;

	if (bus_dmamem_alloc(dmat, &v_addr, flag, dmamap)) {
		printf("fwdma_malloc_size: failed(1)\n");
		return (NULL);
	}
	bus_dmamap_load(dmat, *dmamap, v_addr, size,
			fwdma_map_cb, bus_addr, /*flags*/0);
	return (v_addr);
}