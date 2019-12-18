#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rcvif; void* len; } ;
struct mbuf {TYPE_1__ m_pkthdr; void* m_len; } ;
struct cgem_softc {scalar_t__ rxring_queued; scalar_t__ rxbufs; size_t rxring_hd_ptr; TYPE_2__* rxring; int /*<<< orphan*/ ** rxring_m_dmamap; int /*<<< orphan*/  mbuf_dma_tag; struct mbuf** rxring_m; int /*<<< orphan*/  rxdmamapfails; int /*<<< orphan*/  ifp; } ;
struct TYPE_7__ {int ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;
struct TYPE_6__ {int addr; scalar_t__ ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  CGEM_ASSERT_LOCKED (struct cgem_softc*) ; 
 int CGEM_NUM_RX_DESCS ; 
 int CGEM_RXDESC_WRAP ; 
 void* MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int TX_MAX_DMA_SEGS ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*,TYPE_3__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cgem_fill_rqueue(struct cgem_softc *sc)
{
	struct mbuf *m = NULL;
	bus_dma_segment_t segs[TX_MAX_DMA_SEGS];
	int nsegs;

	CGEM_ASSERT_LOCKED(sc);

	while (sc->rxring_queued < sc->rxbufs) {
		/* Get a cluster mbuf. */
		m = m_getcl(M_NOWAIT, MT_DATA, M_PKTHDR);
		if (m == NULL)
			break;

		m->m_len = MCLBYTES;
		m->m_pkthdr.len = MCLBYTES;
		m->m_pkthdr.rcvif = sc->ifp;

		/* Load map and plug in physical address. */
		if (bus_dmamap_create(sc->mbuf_dma_tag, 0,
			      &sc->rxring_m_dmamap[sc->rxring_hd_ptr])) {
			sc->rxdmamapfails++;
			m_free(m);
			break;
		}
		if (bus_dmamap_load_mbuf_sg(sc->mbuf_dma_tag, 
			      sc->rxring_m_dmamap[sc->rxring_hd_ptr], m,
			      segs, &nsegs, BUS_DMA_NOWAIT)) {
			sc->rxdmamapfails++;
			bus_dmamap_destroy(sc->mbuf_dma_tag,
				   sc->rxring_m_dmamap[sc->rxring_hd_ptr]);
			sc->rxring_m_dmamap[sc->rxring_hd_ptr] = NULL;
			m_free(m);
			break;
		}
		sc->rxring_m[sc->rxring_hd_ptr] = m;

		/* Sync cache with receive buffer. */
		bus_dmamap_sync(sc->mbuf_dma_tag,
				sc->rxring_m_dmamap[sc->rxring_hd_ptr],
				BUS_DMASYNC_PREREAD);

		/* Write rx descriptor and increment head pointer. */
		sc->rxring[sc->rxring_hd_ptr].ctl = 0;
		if (sc->rxring_hd_ptr == CGEM_NUM_RX_DESCS - 1) {
			sc->rxring[sc->rxring_hd_ptr].addr = segs[0].ds_addr |
				CGEM_RXDESC_WRAP;
			sc->rxring_hd_ptr = 0;
		} else
			sc->rxring[sc->rxring_hd_ptr++].addr = segs[0].ds_addr;
			
		sc->rxring_queued++;
	}
}