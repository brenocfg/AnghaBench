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
typedef  int /*<<< orphan*/  uint8_t ;
struct ti_softc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ti_dma_ring_free(struct ti_softc *sc, bus_dma_tag_t *tag, uint8_t **ring,
    bus_dmamap_t map, bus_addr_t *paddr)
{

	if (*paddr != 0) {
		bus_dmamap_unload(*tag, map);
		*paddr = 0;
	}
	if (*ring != NULL) {
		bus_dmamem_free(*tag, *ring, map);
		*ring = NULL;
	}
	if (*tag) {
		bus_dma_tag_destroy(*tag);
		*tag = NULL;
	}
}