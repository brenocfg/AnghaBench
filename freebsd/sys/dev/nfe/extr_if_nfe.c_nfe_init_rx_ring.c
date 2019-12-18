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
struct nfe_softc {int nfe_flags; } ;
struct nfe_rx_ring {int /*<<< orphan*/  rx_desc_map; int /*<<< orphan*/  rx_desc_tag; void* desc32; void* desc64; scalar_t__ next; scalar_t__ cur; } ;
struct nfe_desc64 {int dummy; } ;
struct nfe_desc32 {int dummy; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOBUFS ; 
 int NFE_40BIT_ADDR ; 
 size_t NFE_RX_RING_COUNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 scalar_t__ nfe_newbuf (struct nfe_softc*,int) ; 

__attribute__((used)) static int
nfe_init_rx_ring(struct nfe_softc *sc, struct nfe_rx_ring *ring)
{
	void *desc;
	size_t descsize;
	int i;

	ring->cur = ring->next = 0;
	if (sc->nfe_flags & NFE_40BIT_ADDR) {
		desc = ring->desc64;
		descsize = sizeof (struct nfe_desc64);
	} else {
		desc = ring->desc32;
		descsize = sizeof (struct nfe_desc32);
	}
	bzero(desc, descsize * NFE_RX_RING_COUNT);
	for (i = 0; i < NFE_RX_RING_COUNT; i++) {
		if (nfe_newbuf(sc, i) != 0)
			return (ENOBUFS);
	}

	bus_dmamap_sync(ring->rx_desc_tag, ring->rx_desc_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}