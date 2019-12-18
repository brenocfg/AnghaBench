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
struct ffec_softc {TYPE_1__* txbuf_map; int /*<<< orphan*/  txbuf_tag; } ;
struct bus_dma_segment {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
struct TYPE_2__ {struct mbuf* mbuf; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,struct bus_dma_segment*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffec_setup_txdesc (struct ffec_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffec_setup_txbuf(struct ffec_softc *sc, int idx, struct mbuf **mp)
{
	struct mbuf * m;
	int error, nsegs;
	struct bus_dma_segment seg;

	if ((m = m_defrag(*mp, M_NOWAIT)) == NULL)
		return (ENOMEM);
	*mp = m;

	error = bus_dmamap_load_mbuf_sg(sc->txbuf_tag, sc->txbuf_map[idx].map,
	    m, &seg, &nsegs, 0);
	if (error != 0) {
		return (ENOMEM);
	}
	bus_dmamap_sync(sc->txbuf_tag, sc->txbuf_map[idx].map, 
	    BUS_DMASYNC_PREWRITE);

	sc->txbuf_map[idx].mbuf = m;
	ffec_setup_txdesc(sc, idx, seg.ds_addr, seg.ds_len);

	return (0);

}