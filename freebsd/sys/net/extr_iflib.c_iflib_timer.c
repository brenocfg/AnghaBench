#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* iflib_txq_t ;
typedef  TYPE_2__* if_softc_ctx_t ;
typedef  TYPE_3__* if_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  c_cpu; } ;
struct TYPE_14__ {scalar_t__ isc_pause_frames; } ;
struct TYPE_15__ {int ifc_flags; int /*<<< orphan*/  ifc_ifp; int /*<<< orphan*/  ifc_dev; TYPE_2__ ifc_softc_ctx; } ;
struct TYPE_13__ {int ift_last_timer_tick; scalar_t__ ift_qstatus; scalar_t__ ift_cleaned_prev; scalar_t__ ift_cleaned; int /*<<< orphan*/  ift_pidx; int /*<<< orphan*/  ift_id; TYPE_7__ ift_timer; int /*<<< orphan*/  ift_task; scalar_t__ ift_db_pending; int /*<<< orphan*/  ift_br; TYPE_3__* ift_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPTASK_ENQUEUE (int /*<<< orphan*/ *) ; 
 int IFCAP_NETMAP ; 
 int IFC_DO_RESET ; 
 int IFC_DO_WATCHDOG ; 
 int /*<<< orphan*/  IFDI_TIMER (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ IFLIB_QUEUE_HUNG ; 
 int /*<<< orphan*/  STATE_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  STATE_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  TXQ_AVAIL (TYPE_1__*) ; 
 int /*<<< orphan*/  callout_reset_on (TYPE_7__*,int,void (*) (void*),TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hz ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (TYPE_3__*) ; 
 int /*<<< orphan*/  iflib_netmap_timer_adjust (TYPE_3__*,TYPE_1__*,int*) ; 
 scalar_t__ ifmp_ring_is_stalled (int /*<<< orphan*/ ) ; 
 int ticks ; 

__attribute__((used)) static void
iflib_timer(void *arg)
{
	iflib_txq_t txq = arg;
	if_ctx_t ctx = txq->ift_ctx;
	if_softc_ctx_t sctx = &ctx->ifc_softc_ctx;
	uint64_t this_tick = ticks;
	uint32_t reset_on = hz / 2;

	if (!(if_getdrvflags(ctx->ifc_ifp) & IFF_DRV_RUNNING))
		return;

	/*
	** Check on the state of the TX queue(s), this
	** can be done without the lock because its RO
	** and the HUNG state will be static if set.
	*/
	if (this_tick - txq->ift_last_timer_tick >= hz / 2) {
		txq->ift_last_timer_tick = this_tick;
		IFDI_TIMER(ctx, txq->ift_id);
		if ((txq->ift_qstatus == IFLIB_QUEUE_HUNG) &&
		    ((txq->ift_cleaned_prev == txq->ift_cleaned) ||
		     (sctx->isc_pause_frames == 0)))
			goto hung;

		if (ifmp_ring_is_stalled(txq->ift_br))
			txq->ift_qstatus = IFLIB_QUEUE_HUNG;
		txq->ift_cleaned_prev = txq->ift_cleaned;
	}
#ifdef DEV_NETMAP
	if (if_getcapenable(ctx->ifc_ifp) & IFCAP_NETMAP)
		iflib_netmap_timer_adjust(ctx, txq, &reset_on);
#endif
	/* handle any laggards */
	if (txq->ift_db_pending)
		GROUPTASK_ENQUEUE(&txq->ift_task);

	sctx->isc_pause_frames = 0;
	if (if_getdrvflags(ctx->ifc_ifp) & IFF_DRV_RUNNING) 
		callout_reset_on(&txq->ift_timer, reset_on, iflib_timer, txq, txq->ift_timer.c_cpu);
	return;

 hung:
	device_printf(ctx->ifc_dev,
	    "Watchdog timeout (TX: %d desc avail: %d pidx: %d) -- resetting\n",
	    txq->ift_id, TXQ_AVAIL(txq), txq->ift_pidx);
	STATE_LOCK(ctx);
	if_setdrvflagbits(ctx->ifc_ifp, IFF_DRV_OACTIVE, IFF_DRV_RUNNING);
	ctx->ifc_flags |= (IFC_DO_WATCHDOG|IFC_DO_RESET);
	iflib_admin_intr_deferred(ctx);
	STATE_UNLOCK(ctx);
}