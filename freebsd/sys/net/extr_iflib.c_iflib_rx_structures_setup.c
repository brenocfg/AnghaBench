#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* iflib_rxq_t ;
typedef  TYPE_3__* if_ctx_t ;
struct TYPE_6__ {int isc_nrxqsets; int /*<<< orphan*/ * isc_nrxd; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifc_ifp; TYPE_2__* ifc_rxqs; int /*<<< orphan*/  ifc_dev; TYPE_1__ ifc_softc_ctx; } ;
struct TYPE_7__ {size_t ifr_fl_offset; int /*<<< orphan*/  ifr_lc; int /*<<< orphan*/  ifr_id; } ;

/* Variables and functions */
 int IFCAP_LRO ; 
 int /*<<< orphan*/  IFDI_RXQ_SETUP (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_LRO_ENTRIES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int if_getcapabilities (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_lro_free (int /*<<< orphan*/ *) ; 
 int tcp_lro_init_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iflib_rx_structures_setup(if_ctx_t ctx)
{
	iflib_rxq_t rxq = ctx->ifc_rxqs;
	int q;
#if defined(INET6) || defined(INET)
	int err, i;
#endif

	for (q = 0; q < ctx->ifc_softc_ctx.isc_nrxqsets; q++, rxq++) {
#if defined(INET6) || defined(INET)
		if (if_getcapabilities(ctx->ifc_ifp) & IFCAP_LRO) {
			err = tcp_lro_init_args(&rxq->ifr_lc, ctx->ifc_ifp,
			    TCP_LRO_ENTRIES, min(1024,
			    ctx->ifc_softc_ctx.isc_nrxd[rxq->ifr_fl_offset]));
			if (err != 0) {
				device_printf(ctx->ifc_dev,
				    "LRO Initialization failed!\n");
				goto fail;
			}
		}
#endif
		IFDI_RXQ_SETUP(ctx, rxq->ifr_id);
	}
	return (0);
#if defined(INET6) || defined(INET)
fail:
	/*
	 * Free LRO resources allocated so far, we will only handle
	 * the rings that completed, the failing case will have
	 * cleaned up for itself.  'q' failed, so its the terminus.
	 */
	rxq = ctx->ifc_rxqs;
	for (i = 0; i < q; ++i, rxq++) {
		if (if_getcapabilities(ctx->ifc_ifp) & IFCAP_LRO)
			tcp_lro_free(&rxq->ifr_lc);
	}
	return (err);
#endif
}