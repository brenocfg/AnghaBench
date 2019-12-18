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
typedef  int /*<<< orphan*/  uint8_t ;
struct rtwn_tx_ring {int /*<<< orphan*/  data_dmat; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_dmat; scalar_t__ desc; struct rtwn_tx_data* tx_data; } ;
struct rtwn_tx_desc_common {int flags0; scalar_t__ pktlen; int offset; } ;
struct rtwn_tx_data {int /*<<< orphan*/  map; } ;
struct rtwn_softc {int txdesc_len; int /*<<< orphan*/  sc_dev; } ;
struct rtwn_pci_softc {struct rtwn_tx_ring* tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 int RTWN_FLAGS0_OWN ; 
 size_t RTWN_PCI_BEACON_QUEUE ; 
 struct rtwn_pci_softc* RTWN_PCI_SOFTC (struct rtwn_softc*) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_dump_tx_desc (struct rtwn_softc*,struct rtwn_tx_desc_common*) ; 
 int /*<<< orphan*/  rtwn_pci_copy_tx_desc (struct rtwn_pci_softc*,struct rtwn_tx_desc_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtwn_pci_tx_postsetup (struct rtwn_pci_softc*,struct rtwn_tx_desc_common*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rtwn_pci_tx_start_beacon(struct rtwn_softc *sc, struct mbuf *m,
    uint8_t *tx_desc, int id)
{
	struct rtwn_pci_softc *pc = RTWN_PCI_SOFTC(sc);
	struct rtwn_tx_ring *ring;
	struct rtwn_tx_data *data;
	struct rtwn_tx_desc_common *txd;
	bus_dma_segment_t segs[1];
	int nsegs, error, own;

	RTWN_ASSERT_LOCKED(sc);

	KASSERT(id == 0 || id == 1, ("bogus vap id %d\n", id));

	ring = &pc->tx_ring[RTWN_PCI_BEACON_QUEUE];
	data = &ring->tx_data[id];
	txd = (struct rtwn_tx_desc_common *)
	    ((uint8_t *)ring->desc + id * sc->txdesc_len);

	bus_dmamap_sync(ring->desc_dmat, ring->desc_map,
	    BUS_DMASYNC_POSTREAD);
	own = !!(txd->flags0 & RTWN_FLAGS0_OWN);
	error = 0;
	if (!own || txd->pktlen != htole16(m->m_pkthdr.len)) {
		if (!own) {
			/* Copy Tx descriptor. */
			rtwn_pci_copy_tx_desc(pc, txd, tx_desc);
			txd->offset = sc->txdesc_len;
		} else {
			/* Reload mbuf. */
			bus_dmamap_unload(ring->data_dmat, data->map);
		}

		error = bus_dmamap_load_mbuf_sg(ring->data_dmat,
		    data->map, m, segs, &nsegs, BUS_DMA_NOWAIT);
		if (error != 0) {
			device_printf(sc->sc_dev,
			    "can't map beacon (error %d)\n", error);
			txd->flags0 &= ~RTWN_FLAGS0_OWN;
			goto end;
		}

		txd->pktlen = htole16(m->m_pkthdr.len);
		rtwn_pci_tx_postsetup(pc, txd, segs);
		txd->flags0 |= RTWN_FLAGS0_OWN;
end:
		bus_dmamap_sync(ring->desc_dmat, ring->desc_map,
		    BUS_DMASYNC_PREWRITE);
	}

	/* Dump Tx descriptor. */
	rtwn_dump_tx_desc(sc, txd);

	bus_dmamap_sync(ring->data_dmat, data->map, BUS_DMASYNC_PREWRITE);

	return (0);
}