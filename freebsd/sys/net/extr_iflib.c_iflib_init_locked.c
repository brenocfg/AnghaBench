#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_1__* iflib_txq_t ;
typedef  TYPE_2__* iflib_rxq_t ;
typedef  int /*<<< orphan*/  iflib_fl_t ;
typedef  int /*<<< orphan*/  if_t ;
typedef  TYPE_3__* if_softc_ctx_t ;
typedef  TYPE_4__* if_ctx_t ;
struct TYPE_22__ {int isc_tx_csum_flags; int isc_ntxqsets; int isc_nrxqsets; } ;
struct TYPE_23__ {TYPE_1__* ifc_txqs; int /*<<< orphan*/  ifc_ifp; int /*<<< orphan*/  ifc_dev; TYPE_2__* ifc_rxqs; TYPE_3__ ifc_softc_ctx; } ;
struct TYPE_21__ {int ifr_id; int ifr_nfl; int /*<<< orphan*/  ifr_fl; } ;
struct TYPE_19__ {int /*<<< orphan*/  c_cpu; } ;
struct TYPE_20__ {TYPE_11__ ift_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  CALLOUT_UNLOCK (TYPE_1__*) ; 
 int CSUM_IP ; 
 int CSUM_IP6_SCTP ; 
 int CSUM_IP6_TCP ; 
 int CSUM_IP6_TSO ; 
 int CSUM_IP6_UDP ; 
 int CSUM_IP_TSO ; 
 int CSUM_SCTP ; 
 int CSUM_TCP ; 
 int CSUM_UDP ; 
 int IFCAP_NETMAP ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int /*<<< orphan*/  IFDI_INIT (TYPE_4__*) ; 
 int /*<<< orphan*/  IFDI_INTR_DISABLE (TYPE_4__*) ; 
 int /*<<< orphan*/  IFDI_INTR_ENABLE (TYPE_4__*) ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  callout_reset_on (TYPE_11__*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (TYPE_11__*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int hz ; 
 int /*<<< orphan*/  if_clearhwassist (int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwassistbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_calc_rx_mbuf_sz (TYPE_4__*) ; 
 scalar_t__ iflib_fl_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_netmap_rxq_init (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  iflib_netmap_txq_init (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  iflib_timer ; 

__attribute__((used)) static void
iflib_init_locked(if_ctx_t ctx)
{
	if_softc_ctx_t sctx = &ctx->ifc_softc_ctx;
	if_softc_ctx_t scctx = &ctx->ifc_softc_ctx;
	if_t ifp = ctx->ifc_ifp;
	iflib_fl_t fl;
	iflib_txq_t txq;
	iflib_rxq_t rxq;
	int i, j, tx_ip_csum_flags, tx_ip6_csum_flags;

	if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, IFF_DRV_RUNNING);
	IFDI_INTR_DISABLE(ctx);

	tx_ip_csum_flags = scctx->isc_tx_csum_flags & (CSUM_IP | CSUM_TCP | CSUM_UDP | CSUM_SCTP);
	tx_ip6_csum_flags = scctx->isc_tx_csum_flags & (CSUM_IP6_TCP | CSUM_IP6_UDP | CSUM_IP6_SCTP);
	/* Set hardware offload abilities */
	if_clearhwassist(ifp);
	if (if_getcapenable(ifp) & IFCAP_TXCSUM)
		if_sethwassistbits(ifp, tx_ip_csum_flags, 0);
	if (if_getcapenable(ifp) & IFCAP_TXCSUM_IPV6)
		if_sethwassistbits(ifp,  tx_ip6_csum_flags, 0);
	if (if_getcapenable(ifp) & IFCAP_TSO4)
		if_sethwassistbits(ifp, CSUM_IP_TSO, 0);
	if (if_getcapenable(ifp) & IFCAP_TSO6)
		if_sethwassistbits(ifp, CSUM_IP6_TSO, 0);

	for (i = 0, txq = ctx->ifc_txqs; i < sctx->isc_ntxqsets; i++, txq++) {
		CALLOUT_LOCK(txq);
		callout_stop(&txq->ift_timer);
		CALLOUT_UNLOCK(txq);
		iflib_netmap_txq_init(ctx, txq);
	}

	/*
	 * Calculate a suitable Rx mbuf size prior to calling IFDI_INIT, so
	 * that drivers can use the value when setting up the hardware receive
	 * buffers.
	 */
	iflib_calc_rx_mbuf_sz(ctx);

#ifdef INVARIANTS
	i = if_getdrvflags(ifp);
#endif
	IFDI_INIT(ctx);
	MPASS(if_getdrvflags(ifp) == i);
	for (i = 0, rxq = ctx->ifc_rxqs; i < sctx->isc_nrxqsets; i++, rxq++) {
		/* XXX this should really be done on a per-queue basis */
		if (if_getcapenable(ifp) & IFCAP_NETMAP) {
			MPASS(rxq->ifr_id == i);
			iflib_netmap_rxq_init(ctx, rxq);
			continue;
		}
		for (j = 0, fl = rxq->ifr_fl; j < rxq->ifr_nfl; j++, fl++) {
			if (iflib_fl_setup(fl)) {
				device_printf(ctx->ifc_dev,
				    "setting up free list %d failed - "
				    "check cluster settings\n", j);
				goto done;
			}
		}
	}
done:
	if_setdrvflagbits(ctx->ifc_ifp, IFF_DRV_RUNNING, IFF_DRV_OACTIVE);
	IFDI_INTR_ENABLE(ctx);
	txq = ctx->ifc_txqs;
	for (i = 0; i < sctx->isc_ntxqsets; i++, txq++)
		callout_reset_on(&txq->ift_timer, hz/2, iflib_timer, txq,
			txq->ift_timer.c_cpu);
}