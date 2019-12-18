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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_info {int /*<<< orphan*/  parent_dmat; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_setmap ; 

__attribute__((used)) static void *
emu_malloc(struct sc_info *sc, u_int32_t sz, bus_addr_t *addr,
    bus_dmamap_t *map)
{
	void *buf;

	*addr = 0;
	if (bus_dmamem_alloc(sc->parent_dmat, &buf, BUS_DMA_NOWAIT, map))
		return NULL;
	if (bus_dmamap_load(sc->parent_dmat, *map, buf, sz, emu_setmap, addr, 0)
	    || !*addr) {
		bus_dmamem_free(sc->parent_dmat, buf, *map);
		return NULL;
	}
	return buf;
}