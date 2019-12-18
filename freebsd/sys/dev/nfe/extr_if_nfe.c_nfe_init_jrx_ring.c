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
struct nfe_jrx_ring {int /*<<< orphan*/  jrx_desc_map; int /*<<< orphan*/  jrx_desc_tag; void* jdesc32; void* jdesc64; scalar_t__ jnext; scalar_t__ jcur; } ;
struct nfe_desc64 {int dummy; } ;
struct nfe_desc32 {int dummy; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOBUFS ; 
 int NFE_40BIT_ADDR ; 
 size_t NFE_JUMBO_RX_RING_COUNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 scalar_t__ nfe_jnewbuf (struct nfe_softc*,int) ; 

__attribute__((used)) static int
nfe_init_jrx_ring(struct nfe_softc *sc, struct nfe_jrx_ring *ring)
{
	void *desc;
	size_t descsize;
	int i;

	ring->jcur = ring->jnext = 0;
	if (sc->nfe_flags & NFE_40BIT_ADDR) {
		desc = ring->jdesc64;
		descsize = sizeof (struct nfe_desc64);
	} else {
		desc = ring->jdesc32;
		descsize = sizeof (struct nfe_desc32);
	}
	bzero(desc, descsize * NFE_JUMBO_RX_RING_COUNT);
	for (i = 0; i < NFE_JUMBO_RX_RING_COUNT; i++) {
		if (nfe_jnewbuf(sc, i) != 0)
			return (ENOBUFS);
	}

	bus_dmamap_sync(ring->jrx_desc_tag, ring->jrx_desc_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}