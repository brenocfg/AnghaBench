#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct tx_ring {int tx_tso; int* tx_rsq; size_t tx_rs_pidx; int tx_rs_cidx; struct e1000_tx_desc* tx_base; } ;
struct em_tx_queue {struct tx_ring txr; } ;
struct TYPE_10__ {int data; } ;
struct TYPE_9__ {int data; } ;
struct e1000_tx_desc {TYPE_2__ lower; TYPE_1__ upper; void* buffer_addr; } ;
struct adapter {int txd_cmd; int /*<<< orphan*/  ctx; struct em_tx_queue* tx_queues; TYPE_3__* shared; } ;
typedef  int qidx_t ;
typedef  TYPE_3__* if_softc_ctx_t ;
typedef  TYPE_4__* if_pkt_info_t ;
typedef  int bus_size_t ;
struct TYPE_13__ {int ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_12__ {size_t ipi_qsidx; int ipi_nsegs; int ipi_csum_flags; int ipi_flags; int ipi_pidx; int ipi_mflags; int ipi_new_pidx; int /*<<< orphan*/  ipi_vtag; TYPE_5__* ipi_segs; } ;
struct TYPE_11__ {int* isc_ntxd; } ;

/* Variables and functions */
 int CSUM_TSO ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int E1000_TXD_CMD_EOP ; 
 int E1000_TXD_CMD_IFCS ; 
 int E1000_TXD_CMD_RS ; 
 int E1000_TXD_CMD_VLE ; 
 int EM_CSUM_OFFLOAD ; 
 void* FALSE ; 
 int IPI_TX_INTR ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int M_VLANTAG ; 
 int TRUE ; 
 int TSO_WORKAROUND ; 
 int em_transmit_checksum_setup (struct adapter*,TYPE_4__*,int*,int*) ; 
 int em_tso_setup (struct adapter*,TYPE_4__*,int*,int*) ; 
 int htole16 (int /*<<< orphan*/ ) ; 
 int htole32 (int) ; 
 void* htole64 (scalar_t__) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
em_isc_txd_encap(void *arg, if_pkt_info_t pi)
{
	struct adapter *sc = arg;
	if_softc_ctx_t scctx = sc->shared;
	struct em_tx_queue *que = &sc->tx_queues[pi->ipi_qsidx];
	struct tx_ring *txr = &que->txr;
	bus_dma_segment_t *segs = pi->ipi_segs;
	int nsegs = pi->ipi_nsegs;
	int csum_flags = pi->ipi_csum_flags;
	int i, j, first, pidx_last;
	u32 txd_flags, txd_upper = 0, txd_lower = 0;

	struct e1000_tx_desc *ctxd = NULL;
	bool do_tso, tso_desc;
	qidx_t ntxd;

	txd_flags = pi->ipi_flags & IPI_TX_INTR ? E1000_TXD_CMD_RS : 0;
	i = first = pi->ipi_pidx;
	do_tso = (csum_flags & CSUM_TSO);
	tso_desc = FALSE;
	ntxd = scctx->isc_ntxd[0];
	/*
	 * TSO Hardware workaround, if this packet is not
	 * TSO, and is only a single descriptor long, and
	 * it follows a TSO burst, then we need to add a
	 * sentinel descriptor to prevent premature writeback.
	 */
	if ((!do_tso) && (txr->tx_tso == TRUE)) {
		if (nsegs == 1)
			tso_desc = TRUE;
		txr->tx_tso = FALSE;
	}

	/* Do hardware assists */
	if (do_tso) {
		i = em_tso_setup(sc, pi, &txd_upper, &txd_lower);
		tso_desc = TRUE;
	} else if (csum_flags & EM_CSUM_OFFLOAD) {
		i = em_transmit_checksum_setup(sc, pi, &txd_upper, &txd_lower);
	}

	if (pi->ipi_mflags & M_VLANTAG) {
		/* Set the vlan id. */
		txd_upper |= htole16(pi->ipi_vtag) << 16;
		/* Tell hardware to add tag */
		txd_lower |= htole32(E1000_TXD_CMD_VLE);
	}

	DPRINTF(iflib_get_dev(sc->ctx), "encap: set up tx: nsegs=%d first=%d i=%d\n", nsegs, first, i);
	/* XXX adapter->pcix_82544 -- lem_fill_descriptors */

	/* Set up our transmit descriptors */
	for (j = 0; j < nsegs; j++) {
		bus_size_t seg_len;
		bus_addr_t seg_addr;
		uint32_t cmd;

		ctxd = &txr->tx_base[i];
		seg_addr = segs[j].ds_addr;
		seg_len = segs[j].ds_len;
		cmd = E1000_TXD_CMD_IFCS | sc->txd_cmd;

		/*
		 * TSO Workaround:
		 * If this is the last descriptor, we want to
		 * split it so we have a small final sentinel
		 */
		if (tso_desc && (j == (nsegs - 1)) && (seg_len > 8)) {
			seg_len -= TSO_WORKAROUND;
			ctxd->buffer_addr = htole64(seg_addr);
			ctxd->lower.data = htole32(cmd | txd_lower | seg_len);
			ctxd->upper.data = htole32(txd_upper);

			if (++i == scctx->isc_ntxd[0])
				i = 0;

			/* Now make the sentinel */
			ctxd = &txr->tx_base[i];
			ctxd->buffer_addr = htole64(seg_addr + seg_len);
			ctxd->lower.data = htole32(cmd | txd_lower | TSO_WORKAROUND);
			ctxd->upper.data = htole32(txd_upper);
			pidx_last = i;
			if (++i == scctx->isc_ntxd[0])
				i = 0;
			DPRINTF(iflib_get_dev(sc->ctx), "TSO path pidx_last=%d i=%d ntxd[0]=%d\n", pidx_last, i, scctx->isc_ntxd[0]);
		} else {
			ctxd->buffer_addr = htole64(seg_addr);
			ctxd->lower.data = htole32(cmd | txd_lower | seg_len);
			ctxd->upper.data = htole32(txd_upper);
			pidx_last = i;
			if (++i == scctx->isc_ntxd[0])
				i = 0;
			DPRINTF(iflib_get_dev(sc->ctx), "pidx_last=%d i=%d ntxd[0]=%d\n", pidx_last, i, scctx->isc_ntxd[0]);
		}
	}

	/*
	 * Last Descriptor of Packet
	 * needs End Of Packet (EOP)
	 * and Report Status (RS)
	 */
	if (txd_flags && nsegs) {
		txr->tx_rsq[txr->tx_rs_pidx] = pidx_last;
		DPRINTF(iflib_get_dev(sc->ctx), "setting to RS on %d rs_pidx %d first: %d\n", pidx_last, txr->tx_rs_pidx, first);
		txr->tx_rs_pidx = (txr->tx_rs_pidx+1) & (ntxd-1);
		MPASS(txr->tx_rs_pidx != txr->tx_rs_cidx);
	}
	ctxd->lower.data |= htole32(E1000_TXD_CMD_EOP | txd_flags);
	DPRINTF(iflib_get_dev(sc->ctx), "tx_buffers[%d]->eop = %d ipi_new_pidx=%d\n", first, pidx_last, i);
	pi->ipi_new_pidx = i;

	return (0);
}