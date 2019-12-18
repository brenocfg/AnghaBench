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
struct rtwn_softc {int sc_flags; } ;
struct rtwn_rx_stat_pci {int /*<<< orphan*/  rxdw0; } ;
struct rtwn_rx_ring {size_t cur; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_dmat; struct rtwn_rx_data* rx_data; struct rtwn_rx_stat_pci* desc; } ;
struct rtwn_rx_data {int /*<<< orphan*/  paddr; } ;
struct rtwn_pci_softc {int /*<<< orphan*/  pc_rx_buf; struct rtwn_rx_ring rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MJUMPAGESIZE ; 
 int RTWN_PCI_RX_LIST_COUNT ; 
 struct rtwn_pci_softc* RTWN_PCI_SOFTC (struct rtwn_softc*) ; 
 int RTWN_RUNNING ; 
 int RTWN_RXDW0_OWN ; 
#define  RTWN_RX_DATA 130 
#define  RTWN_RX_OTHER 129 
#define  RTWN_RX_TX_REPORT 128 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int rtwn_classify_intr (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_pci_c2h_report (struct rtwn_pci_softc*,int) ; 
 int rtwn_pci_rx_buf_copy (struct rtwn_pci_softc*) ; 
 int /*<<< orphan*/  rtwn_pci_rx_frame (struct rtwn_pci_softc*) ; 
 int /*<<< orphan*/  rtwn_pci_setup_rx_desc (struct rtwn_pci_softc*,struct rtwn_rx_stat_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rtwn_pci_tx_report (struct rtwn_pci_softc*,int) ; 

__attribute__((used)) static void
rtwn_pci_rx_done(struct rtwn_softc *sc)
{
	struct rtwn_pci_softc *pc = RTWN_PCI_SOFTC(sc);
	struct rtwn_rx_ring *ring = &pc->rx_ring;
	struct rtwn_rx_stat_pci *rx_desc;
	struct rtwn_rx_data *rx_data;
	int len;

	bus_dmamap_sync(ring->desc_dmat, ring->desc_map, BUS_DMASYNC_POSTREAD);

	for (;;) {
		rx_desc = &ring->desc[ring->cur];
		rx_data = &ring->rx_data[ring->cur];

		if (le32toh(rx_desc->rxdw0) & RTWN_RXDW0_OWN)
			break;

		len = rtwn_pci_rx_buf_copy(pc);

		switch (rtwn_classify_intr(sc, pc->pc_rx_buf, len)) {
		case RTWN_RX_DATA:
			rtwn_pci_rx_frame(pc);
			break;
		case RTWN_RX_TX_REPORT:
			rtwn_pci_tx_report(pc, len);
			break;
		case RTWN_RX_OTHER:
			rtwn_pci_c2h_report(pc, len);
			break;
		default:
			/* NOTREACHED */
			KASSERT(0, ("unknown Rx classification code"));
			break;
		}

		/* Update / reset RX descriptor (and set OWN bit). */
		rtwn_pci_setup_rx_desc(pc, rx_desc, rx_data->paddr,
		    MJUMPAGESIZE, ring->cur);

		if (!(sc->sc_flags & RTWN_RUNNING))
			return;

		/* NB: device can reuse current descriptor. */
		bus_dmamap_sync(ring->desc_dmat, ring->desc_map,
		    BUS_DMASYNC_POSTREAD);

		if (le32toh(rx_desc->rxdw0) & RTWN_RXDW0_OWN)
			ring->cur = (ring->cur + 1) % RTWN_PCI_RX_LIST_COUNT;
	}
}