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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct hn_txdesc {int /*<<< orphan*/  flags; int /*<<< orphan*/  rndis_pkt_dmap; int /*<<< orphan*/  rndis_pkt; int /*<<< orphan*/  data_dmap; int /*<<< orphan*/  rndis_pkt_paddr; int /*<<< orphan*/  agg_list; int /*<<< orphan*/  chim_index; struct hn_tx_ring* txr; } ;
struct hn_tx_ring {int hn_tx_idx; int hn_txdesc_cnt; int hn_sched_tx; int hn_txdesc_avail; int hn_oactive; int /*<<< orphan*/  hn_sends; int /*<<< orphan*/  hn_pkts; int /*<<< orphan*/ * hn_tx_sysctl_tree; void* hn_txdesc_br; int /*<<< orphan*/  hn_txlist; int /*<<< orphan*/  hn_tx_rndis_dtag; int /*<<< orphan*/  hn_tx_data_dtag; struct hn_txdesc* hn_txdesc; int /*<<< orphan*/  hn_direct_tx_size; int /*<<< orphan*/  hn_tx_lock; void* hn_mbuf_br; int /*<<< orphan*/  hn_txeof_task; int /*<<< orphan*/  hn_tx_task; int /*<<< orphan*/  hn_txeof; int /*<<< orphan*/  hn_tx_taskq; int /*<<< orphan*/  hn_txlist_spin; struct hn_softc* hn_sc; } ;
struct hn_softc {int /*<<< orphan*/ * hn_tx_sysctl_tree; int /*<<< orphan*/ * hn_tx_taskqs; int /*<<< orphan*/  hn_dev; struct hn_tx_ring* hn_tx_ring; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  HN_NVS_CHIM_IDX_INVALID ; 
 int /*<<< orphan*/  HN_RING_IDX2CPU (struct hn_softc*,int) ; 
 int HN_RNDIS_PKT_ALIGN ; 
 int /*<<< orphan*/  HN_RNDIS_PKT_BOUNDARY ; 
 int /*<<< orphan*/  HN_RNDIS_PKT_LEN ; 
 int /*<<< orphan*/  HN_TXD_FLAG_ONLIST ; 
 int /*<<< orphan*/  HN_TX_DATA_BOUNDARY ; 
 int /*<<< orphan*/  HN_TX_DATA_MAXSIZE ; 
 int HN_TX_DATA_SEGCNT_MAX ; 
 int /*<<< orphan*/  HN_TX_DATA_SEGSIZE ; 
 int HN_TX_DESC_CNT ; 
 scalar_t__ HN_TX_TASKQ_M_EVTTQ ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct hn_txdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_ULONG (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hn_tx_ring*) ; 
 int /*<<< orphan*/  VMBUS_GET_EVENT_TASKQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* buf_ring_alloc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_ring_enqueue (void*,struct hn_txdesc*) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hn_direct_tx_size ; 
 int hn_get_txswq_depth (struct hn_tx_ring*) ; 
 int /*<<< orphan*/  hn_start_taskfunc ; 
 int /*<<< orphan*/  hn_start_txeof ; 
 int /*<<< orphan*/  hn_start_txeof_taskfunc ; 
 int hn_tx_taskq_cnt ; 
 scalar_t__ hn_tx_taskq_mode ; 
 scalar_t__ hn_use_if_start ; 
 int /*<<< orphan*/  hn_xmit_taskfunc ; 
 int /*<<< orphan*/  hn_xmit_txeof ; 
 int /*<<< orphan*/  hn_xmit_txeof_taskfunc ; 
 int /*<<< orphan*/  hyperv_dma_map_paddr ; 
 int /*<<< orphan*/  link ; 
 struct hn_txdesc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
hn_tx_ring_create(struct hn_softc *sc, int id)
{
	struct hn_tx_ring *txr = &sc->hn_tx_ring[id];
	device_t dev = sc->hn_dev;
	bus_dma_tag_t parent_dtag;
	int error, i;

	txr->hn_sc = sc;
	txr->hn_tx_idx = id;

#ifndef HN_USE_TXDESC_BUFRING
	mtx_init(&txr->hn_txlist_spin, "hn txlist", NULL, MTX_SPIN);
#endif
	mtx_init(&txr->hn_tx_lock, "hn tx", NULL, MTX_DEF);

	txr->hn_txdesc_cnt = HN_TX_DESC_CNT;
	txr->hn_txdesc = malloc(sizeof(struct hn_txdesc) * txr->hn_txdesc_cnt,
	    M_DEVBUF, M_WAITOK | M_ZERO);
#ifndef HN_USE_TXDESC_BUFRING
	SLIST_INIT(&txr->hn_txlist);
#else
	txr->hn_txdesc_br = buf_ring_alloc(txr->hn_txdesc_cnt, M_DEVBUF,
	    M_WAITOK, &txr->hn_tx_lock);
#endif

	if (hn_tx_taskq_mode == HN_TX_TASKQ_M_EVTTQ) {
		txr->hn_tx_taskq = VMBUS_GET_EVENT_TASKQ(
		    device_get_parent(dev), dev, HN_RING_IDX2CPU(sc, id));
	} else {
		txr->hn_tx_taskq = sc->hn_tx_taskqs[id % hn_tx_taskq_cnt];
	}

#ifdef HN_IFSTART_SUPPORT
	if (hn_use_if_start) {
		txr->hn_txeof = hn_start_txeof;
		TASK_INIT(&txr->hn_tx_task, 0, hn_start_taskfunc, txr);
		TASK_INIT(&txr->hn_txeof_task, 0, hn_start_txeof_taskfunc, txr);
	} else
#endif
	{
		int br_depth;

		txr->hn_txeof = hn_xmit_txeof;
		TASK_INIT(&txr->hn_tx_task, 0, hn_xmit_taskfunc, txr);
		TASK_INIT(&txr->hn_txeof_task, 0, hn_xmit_txeof_taskfunc, txr);

		br_depth = hn_get_txswq_depth(txr);
		txr->hn_mbuf_br = buf_ring_alloc(br_depth, M_DEVBUF,
		    M_WAITOK, &txr->hn_tx_lock);
	}

	txr->hn_direct_tx_size = hn_direct_tx_size;

	/*
	 * Always schedule transmission instead of trying to do direct
	 * transmission.  This one gives the best performance so far.
	 */
	txr->hn_sched_tx = 1;

	parent_dtag = bus_get_dma_tag(dev);

	/* DMA tag for RNDIS packet messages. */
	error = bus_dma_tag_create(parent_dtag, /* parent */
	    HN_RNDIS_PKT_ALIGN,		/* alignment */
	    HN_RNDIS_PKT_BOUNDARY,	/* boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    HN_RNDIS_PKT_LEN,		/* maxsize */
	    1,				/* nsegments */
	    HN_RNDIS_PKT_LEN,		/* maxsegsize */
	    0,				/* flags */
	    NULL,			/* lockfunc */
	    NULL,			/* lockfuncarg */
	    &txr->hn_tx_rndis_dtag);
	if (error) {
		device_printf(dev, "failed to create rndis dmatag\n");
		return error;
	}

	/* DMA tag for data. */
	error = bus_dma_tag_create(parent_dtag, /* parent */
	    1,				/* alignment */
	    HN_TX_DATA_BOUNDARY,	/* boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    HN_TX_DATA_MAXSIZE,		/* maxsize */
	    HN_TX_DATA_SEGCNT_MAX,	/* nsegments */
	    HN_TX_DATA_SEGSIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL,			/* lockfunc */
	    NULL,			/* lockfuncarg */
	    &txr->hn_tx_data_dtag);
	if (error) {
		device_printf(dev, "failed to create data dmatag\n");
		return error;
	}

	for (i = 0; i < txr->hn_txdesc_cnt; ++i) {
		struct hn_txdesc *txd = &txr->hn_txdesc[i];

		txd->txr = txr;
		txd->chim_index = HN_NVS_CHIM_IDX_INVALID;
		STAILQ_INIT(&txd->agg_list);

		/*
		 * Allocate and load RNDIS packet message.
		 */
        	error = bus_dmamem_alloc(txr->hn_tx_rndis_dtag,
		    (void **)&txd->rndis_pkt,
		    BUS_DMA_WAITOK | BUS_DMA_COHERENT | BUS_DMA_ZERO,
		    &txd->rndis_pkt_dmap);
		if (error) {
			device_printf(dev,
			    "failed to allocate rndis_packet_msg, %d\n", i);
			return error;
		}

		error = bus_dmamap_load(txr->hn_tx_rndis_dtag,
		    txd->rndis_pkt_dmap,
		    txd->rndis_pkt, HN_RNDIS_PKT_LEN,
		    hyperv_dma_map_paddr, &txd->rndis_pkt_paddr,
		    BUS_DMA_NOWAIT);
		if (error) {
			device_printf(dev,
			    "failed to load rndis_packet_msg, %d\n", i);
			bus_dmamem_free(txr->hn_tx_rndis_dtag,
			    txd->rndis_pkt, txd->rndis_pkt_dmap);
			return error;
		}

		/* DMA map for TX data. */
		error = bus_dmamap_create(txr->hn_tx_data_dtag, 0,
		    &txd->data_dmap);
		if (error) {
			device_printf(dev,
			    "failed to allocate tx data dmamap\n");
			bus_dmamap_unload(txr->hn_tx_rndis_dtag,
			    txd->rndis_pkt_dmap);
			bus_dmamem_free(txr->hn_tx_rndis_dtag,
			    txd->rndis_pkt, txd->rndis_pkt_dmap);
			return error;
		}

		/* All set, put it to list */
		txd->flags |= HN_TXD_FLAG_ONLIST;
#ifndef HN_USE_TXDESC_BUFRING
		SLIST_INSERT_HEAD(&txr->hn_txlist, txd, link);
#else
		buf_ring_enqueue(txr->hn_txdesc_br, txd);
#endif
	}
	txr->hn_txdesc_avail = txr->hn_txdesc_cnt;

	if (sc->hn_tx_sysctl_tree != NULL) {
		struct sysctl_oid_list *child;
		struct sysctl_ctx_list *ctx;
		char name[16];

		/*
		 * Create per TX ring sysctl tree:
		 * dev.hn.UNIT.tx.RINGID
		 */
		ctx = device_get_sysctl_ctx(dev);
		child = SYSCTL_CHILDREN(sc->hn_tx_sysctl_tree);

		snprintf(name, sizeof(name), "%d", id);
		txr->hn_tx_sysctl_tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO,
		    name, CTLFLAG_RD | CTLFLAG_MPSAFE, 0, "");

		if (txr->hn_tx_sysctl_tree != NULL) {
			child = SYSCTL_CHILDREN(txr->hn_tx_sysctl_tree);

#ifdef HN_DEBUG
			SYSCTL_ADD_INT(ctx, child, OID_AUTO, "txdesc_avail",
			    CTLFLAG_RD, &txr->hn_txdesc_avail, 0,
			    "# of available TX descs");
#endif
#ifdef HN_IFSTART_SUPPORT
			if (!hn_use_if_start)
#endif
			{
				SYSCTL_ADD_INT(ctx, child, OID_AUTO, "oactive",
				    CTLFLAG_RD, &txr->hn_oactive, 0,
				    "over active");
			}
			SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "packets",
			    CTLFLAG_RW, &txr->hn_pkts,
			    "# of packets transmitted");
			SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "sends",
			    CTLFLAG_RW, &txr->hn_sends, "# of sends");
		}
	}

	return 0;
}