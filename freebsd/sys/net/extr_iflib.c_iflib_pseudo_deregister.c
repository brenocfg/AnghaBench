#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct taskqgroup {int dummy; } ;
typedef  TYPE_1__* iflib_txq_t ;
typedef  TYPE_2__* iflib_rxq_t ;
typedef  TYPE_3__* iflib_fl_t ;
typedef  int /*<<< orphan*/  if_t ;
typedef  TYPE_4__* if_ctx_t ;
struct TYPE_18__ {int /*<<< orphan*/ * gt_uniq; } ;
struct TYPE_17__ {int ifc_flags; struct TYPE_17__* ifc_softc; TYPE_5__ ifc_vflr_task; TYPE_5__ ifc_admin_task; TYPE_2__* ifc_rxqs; TYPE_1__* ifc_txqs; int /*<<< orphan*/  ifc_ifp; } ;
struct TYPE_16__ {TYPE_4__* ifl_rx_bitmap; } ;
struct TYPE_15__ {int ifr_nfl; TYPE_3__* ifr_fl; TYPE_5__ ifr_task; } ;
struct TYPE_14__ {TYPE_5__ ift_task; int /*<<< orphan*/  ift_timer; } ;

/* Variables and functions */
 int IFC_SC_ALLOCATED ; 
 int /*<<< orphan*/  M_IFLIB ; 
 int NRXQSETS (TYPE_4__*) ; 
 int NTXQSETS (TYPE_4__*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_deregister (TYPE_4__*) ; 
 int /*<<< orphan*/  iflib_rx_structures_free (TYPE_4__*) ; 
 int /*<<< orphan*/  iflib_tx_structures_free (TYPE_4__*) ; 
 int /*<<< orphan*/  iflib_unregister_vlan_handlers (TYPE_4__*) ; 
 struct taskqgroup* qgroup_if_config_tqg ; 
 struct taskqgroup* qgroup_if_io_tqg ; 
 int /*<<< orphan*/  taskqgroup_detach (struct taskqgroup*,TYPE_5__*) ; 

int
iflib_pseudo_deregister(if_ctx_t ctx)
{
	if_t ifp = ctx->ifc_ifp;
	iflib_txq_t txq;
	iflib_rxq_t rxq;
	int i, j;
	struct taskqgroup *tqg;
	iflib_fl_t fl;

	/* Unregister VLAN event handlers early */
	iflib_unregister_vlan_handlers(ctx);

	ether_ifdetach(ifp);
	/* XXX drain any dependent tasks */
	tqg = qgroup_if_io_tqg;
	for (txq = ctx->ifc_txqs, i = 0; i < NTXQSETS(ctx); i++, txq++) {
		callout_drain(&txq->ift_timer);
		if (txq->ift_task.gt_uniq != NULL)
			taskqgroup_detach(tqg, &txq->ift_task);
	}
	for (i = 0, rxq = ctx->ifc_rxqs; i < NRXQSETS(ctx); i++, rxq++) {
		if (rxq->ifr_task.gt_uniq != NULL)
			taskqgroup_detach(tqg, &rxq->ifr_task);

		for (j = 0, fl = rxq->ifr_fl; j < rxq->ifr_nfl; j++, fl++)
			free(fl->ifl_rx_bitmap, M_IFLIB);
	}
	tqg = qgroup_if_config_tqg;
	if (ctx->ifc_admin_task.gt_uniq != NULL)
		taskqgroup_detach(tqg, &ctx->ifc_admin_task);
	if (ctx->ifc_vflr_task.gt_uniq != NULL)
		taskqgroup_detach(tqg, &ctx->ifc_vflr_task);

	iflib_tx_structures_free(ctx);
	iflib_rx_structures_free(ctx);

	iflib_deregister(ctx);

	if (ctx->ifc_flags & IFC_SC_ALLOCATED)
		free(ctx->ifc_softc, M_IFLIB);
	free(ctx, M_IFLIB);
	return (0);
}