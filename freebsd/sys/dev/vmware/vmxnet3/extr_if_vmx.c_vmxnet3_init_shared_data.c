#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  vxcr_ndesc; int /*<<< orphan*/  vxcr_paddr; } ;
struct TYPE_15__ {int /*<<< orphan*/  vxcr_ndesc; int /*<<< orphan*/  vxcr_paddr; } ;
struct TYPE_14__ {int /*<<< orphan*/  vxtxr_ndesc; int /*<<< orphan*/  vxtxr_paddr; } ;
struct TYPE_13__ {int /*<<< orphan*/  idi_size; int /*<<< orphan*/  idi_paddr; } ;
struct TYPE_12__ {int /*<<< orphan*/  idi_size; int /*<<< orphan*/  idi_paddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  idi_size; int /*<<< orphan*/  idi_paddr; } ;
struct vmxnet3_txqueue {int vmx_flags; scalar_t__ vmx_intr_mask_mode; TYPE_8__ vxrxq_comp_ring; TYPE_7__* vxrxq_cmd_ring; struct vmxnet3_rxq_shared* vxrxq_rs; struct vmxnet3_txqueue* vmx_rxq; TYPE_6__ vxtxq_comp_ring; TYPE_5__ vxtxq_cmd_ring; struct vmxnet3_txq_shared* vxtxq_ts; struct vmxnet3_txqueue* vmx_txq; TYPE_4__ vmx_mcast_dma; int /*<<< orphan*/  vmx_event_intr_idx; TYPE_3__ vmx_rss_dma; TYPE_1__ vmx_qs_dma; TYPE_9__* vmx_scctx; int /*<<< orphan*/  vmx_sctx; struct vmxnet3_driver_shared* vmx_ds; } ;
struct vmxnet3_txq_shared {int driver_data_len; void* driver_data; int /*<<< orphan*/  comp_ring_len; int /*<<< orphan*/  comp_ring; int /*<<< orphan*/  cmd_ring_len; int /*<<< orphan*/  cmd_ring; } ;
struct vmxnet3_softc {int vmx_flags; scalar_t__ vmx_intr_mask_mode; TYPE_8__ vxrxq_comp_ring; TYPE_7__* vxrxq_cmd_ring; struct vmxnet3_rxq_shared* vxrxq_rs; struct vmxnet3_softc* vmx_rxq; TYPE_6__ vxtxq_comp_ring; TYPE_5__ vxtxq_cmd_ring; struct vmxnet3_txq_shared* vxtxq_ts; struct vmxnet3_softc* vmx_txq; TYPE_4__ vmx_mcast_dma; int /*<<< orphan*/  vmx_event_intr_idx; TYPE_3__ vmx_rss_dma; TYPE_1__ vmx_qs_dma; TYPE_9__* vmx_scctx; int /*<<< orphan*/  vmx_sctx; struct vmxnet3_driver_shared* vmx_ds; } ;
struct vmxnet3_rxqueue {int vmx_flags; scalar_t__ vmx_intr_mask_mode; TYPE_8__ vxrxq_comp_ring; TYPE_7__* vxrxq_cmd_ring; struct vmxnet3_rxq_shared* vxrxq_rs; struct vmxnet3_rxqueue* vmx_rxq; TYPE_6__ vxtxq_comp_ring; TYPE_5__ vxtxq_cmd_ring; struct vmxnet3_txq_shared* vxtxq_ts; struct vmxnet3_rxqueue* vmx_txq; TYPE_4__ vmx_mcast_dma; int /*<<< orphan*/  vmx_event_intr_idx; TYPE_3__ vmx_rss_dma; TYPE_1__ vmx_qs_dma; TYPE_9__* vmx_scctx; int /*<<< orphan*/  vmx_sctx; struct vmxnet3_driver_shared* vmx_ds; } ;
struct vmxnet3_rxq_shared {int driver_data_len; void* driver_data; int /*<<< orphan*/  comp_ring_len; int /*<<< orphan*/  comp_ring; int /*<<< orphan*/ * cmd_ring_len; int /*<<< orphan*/ * cmd_ring; } ;
struct TYPE_11__ {int version; int /*<<< orphan*/  len; int /*<<< orphan*/  paddr; } ;
struct vmxnet3_driver_shared {int guest; int vmxnet3_revision; int upt_version; int driver_data_len; int automask; int nintr; int /*<<< orphan*/  mcast_tablelen; int /*<<< orphan*/  mcast_table; int /*<<< orphan*/ * modlevel; int /*<<< orphan*/  ictrl; int /*<<< orphan*/  evintr; TYPE_2__ rss; int /*<<< orphan*/  nrxsg_max; int /*<<< orphan*/  queue_shared_len; int /*<<< orphan*/  queue_shared; void* driver_data; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  TYPE_9__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_shared_ctx_t ;
struct TYPE_18__ {int isc_vectors; int isc_nrxqsets; int isc_ntxqsets; } ;
struct TYPE_16__ {int /*<<< orphan*/  vxrxr_ndesc; int /*<<< orphan*/  vxrxr_paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLIB_MAX_RX_SEGS ; 
 int /*<<< orphan*/  UPT1_IMOD_ADAPTIVE ; 
 int /*<<< orphan*/  VMXNET3_DRIVER_VERSION ; 
 int VMXNET3_FLAG_RSS ; 
 int /*<<< orphan*/  VMXNET3_GOS_32BIT ; 
 int VMXNET3_GOS_64BIT ; 
 int VMXNET3_GOS_FREEBSD ; 
 int /*<<< orphan*/  VMXNET3_ICTRL_DISABLE_ALL ; 
 scalar_t__ VMXNET3_IMM_AUTO ; 
 int /*<<< orphan*/  VMXNET3_REV1_MAGIC ; 
 void* vtophys (struct vmxnet3_txqueue*) ; 

__attribute__((used)) static void
vmxnet3_init_shared_data(struct vmxnet3_softc *sc)
{
	struct vmxnet3_driver_shared *ds;
	if_shared_ctx_t sctx;
	if_softc_ctx_t scctx;
	struct vmxnet3_txqueue *txq;
	struct vmxnet3_txq_shared *txs;
	struct vmxnet3_rxqueue *rxq;
	struct vmxnet3_rxq_shared *rxs;
	int i;

	ds = sc->vmx_ds;
	sctx = sc->vmx_sctx;
	scctx = sc->vmx_scctx;

	/*
	 * Initialize fields of the shared data that remains the same across
	 * reinits. Note the shared data is zero'd when allocated.
	 */

	ds->magic = VMXNET3_REV1_MAGIC;

	/* DriverInfo */
	ds->version = VMXNET3_DRIVER_VERSION;
	ds->guest = VMXNET3_GOS_FREEBSD |
#ifdef __LP64__
	    VMXNET3_GOS_64BIT;
#else
	    VMXNET3_GOS_32BIT;
#endif
	ds->vmxnet3_revision = 1;
	ds->upt_version = 1;

	/* Misc. conf */
	ds->driver_data = vtophys(sc);
	ds->driver_data_len = sizeof(struct vmxnet3_softc);
	ds->queue_shared = sc->vmx_qs_dma.idi_paddr;
	ds->queue_shared_len = sc->vmx_qs_dma.idi_size;
	ds->nrxsg_max = IFLIB_MAX_RX_SEGS;

	/* RSS conf */
	if (sc->vmx_flags & VMXNET3_FLAG_RSS) {
		ds->rss.version = 1;
		ds->rss.paddr = sc->vmx_rss_dma.idi_paddr;
		ds->rss.len = sc->vmx_rss_dma.idi_size;
	}

	/* Interrupt control. */
	ds->automask = sc->vmx_intr_mask_mode == VMXNET3_IMM_AUTO;
	/*
	 * Total number of interrupt indexes we are using in the shared
	 * config data, even though we don't actually allocate interrupt
	 * resources for the tx queues.  Some versions of the device will
	 * fail to initialize successfully if interrupt indexes are used in
	 * the shared config that exceed the number of interrupts configured
	 * here.
	 */
	ds->nintr = (scctx->isc_vectors == 1) ?
	    2 : (scctx->isc_nrxqsets + scctx->isc_ntxqsets + 1);
	ds->evintr = sc->vmx_event_intr_idx;
	ds->ictrl = VMXNET3_ICTRL_DISABLE_ALL;

	for (i = 0; i < ds->nintr; i++)
		ds->modlevel[i] = UPT1_IMOD_ADAPTIVE;

	/* Receive filter. */
	ds->mcast_table = sc->vmx_mcast_dma.idi_paddr;
	ds->mcast_tablelen = sc->vmx_mcast_dma.idi_size;

	/* Tx queues */
	for (i = 0; i < scctx->isc_ntxqsets; i++) {
		txq = &sc->vmx_txq[i];
		txs = txq->vxtxq_ts;

		txs->cmd_ring = txq->vxtxq_cmd_ring.vxtxr_paddr;
		txs->cmd_ring_len = txq->vxtxq_cmd_ring.vxtxr_ndesc;
		txs->comp_ring = txq->vxtxq_comp_ring.vxcr_paddr;
		txs->comp_ring_len = txq->vxtxq_comp_ring.vxcr_ndesc;
		txs->driver_data = vtophys(txq);
		txs->driver_data_len = sizeof(struct vmxnet3_txqueue);
	}

	/* Rx queues */
	for (i = 0; i < scctx->isc_nrxqsets; i++) {
		rxq = &sc->vmx_rxq[i];
		rxs = rxq->vxrxq_rs;

		rxs->cmd_ring[0] = rxq->vxrxq_cmd_ring[0].vxrxr_paddr;
		rxs->cmd_ring_len[0] = rxq->vxrxq_cmd_ring[0].vxrxr_ndesc;
		rxs->cmd_ring[1] = rxq->vxrxq_cmd_ring[1].vxrxr_paddr;
		rxs->cmd_ring_len[1] = rxq->vxrxq_cmd_ring[1].vxrxr_ndesc;
		rxs->comp_ring = rxq->vxrxq_comp_ring.vxcr_paddr;
		rxs->comp_ring_len = rxq->vxrxq_comp_ring.vxcr_ndesc;
		rxs->driver_data = vtophys(rxq);
		rxs->driver_data_len = sizeof(struct vmxnet3_rxqueue);
	}
}