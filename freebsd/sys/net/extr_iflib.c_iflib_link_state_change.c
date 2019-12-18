#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_2__* iflib_txq_t ;
typedef  int /*<<< orphan*/  if_t ;
typedef  TYPE_3__* if_ctx_t ;
struct TYPE_7__ {int isc_ntxqsets; } ;
struct TYPE_9__ {int ifc_link_state; TYPE_1__ ifc_softc_ctx; int /*<<< orphan*/  ifc_flags; TYPE_2__* ifc_txqs; int /*<<< orphan*/  ifc_ifp; } ;
struct TYPE_8__ {int /*<<< orphan*/  ift_qstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFC_PREFETCH ; 
 int /*<<< orphan*/  IFLIB_QUEUE_IDLE ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int LINK_STATE_DOWN ; 
 int LINK_STATE_UP ; 
 int /*<<< orphan*/  STATE_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  STATE_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setbaudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iflib_link_state_change(if_ctx_t ctx, int link_state, uint64_t baudrate)
{
	if_t ifp = ctx->ifc_ifp;
	iflib_txq_t txq = ctx->ifc_txqs;

	if_setbaudrate(ifp, baudrate);
	if (baudrate >= IF_Gbps(10)) {
		STATE_LOCK(ctx);
		ctx->ifc_flags |= IFC_PREFETCH;
		STATE_UNLOCK(ctx);
	}
	/* If link down, disable watchdog */
	if ((ctx->ifc_link_state == LINK_STATE_UP) && (link_state == LINK_STATE_DOWN)) {
		for (int i = 0; i < ctx->ifc_softc_ctx.isc_ntxqsets; i++, txq++)
			txq->ift_qstatus = IFLIB_QUEUE_IDLE;
	}
	ctx->ifc_link_state = link_state;
	if_link_state_change(ifp, link_state);
}