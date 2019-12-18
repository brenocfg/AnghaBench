#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* iflib_txq_t ;
typedef  TYPE_3__* if_t ;
typedef  TYPE_4__* if_ctx_t ;
struct TYPE_14__ {int ifc_sysctl_tx_abdicate; int ifc_flags; int /*<<< orphan*/  ifc_softc; scalar_t__ (* isc_txd_credits_update ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;TYPE_3__* ifc_ifp; } ;
struct TYPE_13__ {int /*<<< orphan*/  if_snd; } ;
struct TYPE_12__ {int /*<<< orphan*/  ift_id; int /*<<< orphan*/  ift_br; scalar_t__ ift_db_pending; TYPE_1__* ift_ifdi; int /*<<< orphan*/ * ift_cpu_exec_count; TYPE_4__* ift_ctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  idi_map; int /*<<< orphan*/  idi_tag; } ;

/* Variables and functions */
 scalar_t__ ALTQ_IS_ENABLED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int IFCAP_NETMAP ; 
 int IFC_LEGACY ; 
 int /*<<< orphan*/  IFDI_INTR_ENABLE (TYPE_4__*) ; 
 int /*<<< orphan*/  IFDI_TX_QUEUE_INTR_ENABLE (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  TX_BATCH_SIZE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t curcpu ; 
 int if_getcapenable (TYPE_3__*) ; 
 int if_getdrvflags (TYPE_3__*) ; 
 int /*<<< orphan*/  iflib_altq_if_start (TYPE_3__*) ; 
 int /*<<< orphan*/  ifmp_ring_check_drainage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmp_ring_enqueue (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netmap_tx_irq (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
_task_fn_tx(void *context)
{
	iflib_txq_t txq = context;
	if_ctx_t ctx = txq->ift_ctx;
#if defined(ALTQ) || defined(DEV_NETMAP)
	if_t ifp = ctx->ifc_ifp;
#endif
	int abdicate = ctx->ifc_sysctl_tx_abdicate;

#ifdef IFLIB_DIAGNOSTICS
	txq->ift_cpu_exec_count[curcpu]++;
#endif
	if (!(if_getdrvflags(ctx->ifc_ifp) & IFF_DRV_RUNNING))
		return;
#ifdef DEV_NETMAP
	if (if_getcapenable(ifp) & IFCAP_NETMAP) {
		bus_dmamap_sync(txq->ift_ifdi->idi_tag, txq->ift_ifdi->idi_map,
		    BUS_DMASYNC_POSTREAD);
		if (ctx->isc_txd_credits_update(ctx->ifc_softc, txq->ift_id, false))
			netmap_tx_irq(ifp, txq->ift_id);
		if (ctx->ifc_flags & IFC_LEGACY)
			IFDI_INTR_ENABLE(ctx);
		else
			IFDI_TX_QUEUE_INTR_ENABLE(ctx, txq->ift_id);
		return;
	}
#endif
#ifdef ALTQ
	if (ALTQ_IS_ENABLED(&ifp->if_snd))
		iflib_altq_if_start(ifp);
#endif
	if (txq->ift_db_pending)
		ifmp_ring_enqueue(txq->ift_br, (void **)&txq, 1, TX_BATCH_SIZE, abdicate);
	else if (!abdicate)
		ifmp_ring_check_drainage(txq->ift_br, TX_BATCH_SIZE);
	/*
	 * When abdicating, we always need to check drainage, not just when we don't enqueue
	 */
	if (abdicate)
		ifmp_ring_check_drainage(txq->ift_br, TX_BATCH_SIZE);
	if (ctx->ifc_flags & IFC_LEGACY)
		IFDI_INTR_ENABLE(ctx);
	else
		IFDI_TX_QUEUE_INTR_ENABLE(ctx, txq->ift_id);
}