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
struct bwn_dma_ring {int /*<<< orphan*/  dr_ring_dmap; int /*<<< orphan*/  dr_ring_descbase; int /*<<< orphan*/  dr_ring_dtag; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_dma_free_ringmemory(struct bwn_dma_ring *dr)
{

	bus_dmamap_unload(dr->dr_ring_dtag, dr->dr_ring_dmap);
	bus_dmamem_free(dr->dr_ring_dtag, dr->dr_ring_descbase,
	    dr->dr_ring_dmap);
}