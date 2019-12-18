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
struct mbuf {int dummy; } ;
struct ffec_softc {int fecflags; TYPE_1__* rxbuf_map; int /*<<< orphan*/  rxbuf_tag; int /*<<< orphan*/  rxbuf_align; } ;
struct bus_dma_segment {int /*<<< orphan*/  ds_addr; } ;
struct TYPE_2__ {struct mbuf* mbuf; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  ETHER_ALIGN ; 
 int FECFLAG_RACC ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,struct bus_dma_segment*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffec_setup_rxdesc (struct ffec_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffec_setup_rxbuf(struct ffec_softc *sc, int idx, struct mbuf * m)
{
	int error, nsegs;
	struct bus_dma_segment seg;

	if (!(sc->fecflags & FECFLAG_RACC)) {
		/*
		 * The RACC[SHIFT16] feature is not available.  So, we need to
		 * leave at least ETHER_ALIGN bytes free at the beginning of the
		 * buffer to allow the data to be re-aligned after receiving it
		 * (by copying it backwards ETHER_ALIGN bytes in the same
		 * buffer).  We also have to ensure that the beginning of the
		 * buffer is aligned to the hardware's requirements.
		 */
		m_adj(m, roundup(ETHER_ALIGN, sc->rxbuf_align));
	}

	error = bus_dmamap_load_mbuf_sg(sc->rxbuf_tag, sc->rxbuf_map[idx].map,
	    m, &seg, &nsegs, 0);
	if (error != 0) {
		return (error);
	}

	bus_dmamap_sync(sc->rxbuf_tag, sc->rxbuf_map[idx].map, 
	    BUS_DMASYNC_PREREAD);

	sc->rxbuf_map[idx].mbuf = m;
	ffec_setup_rxdesc(sc, idx, seg.ds_addr);
	
	return (0);
}