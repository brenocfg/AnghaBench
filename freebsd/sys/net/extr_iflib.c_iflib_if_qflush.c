#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iflib_txq_t ;
typedef  int /*<<< orphan*/  if_t ;
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  ifc_flags; TYPE_1__* ifc_txqs; } ;
struct TYPE_8__ {int /*<<< orphan*/  ift_br; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFC_QFLUSH ; 
 int NTXQSETS (TYPE_2__*) ; 
 int /*<<< orphan*/  STATE_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  STATE_UNLOCK (TYPE_2__*) ; 
 TYPE_2__* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_qflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_txq_check_drain (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ifmp_ring_is_idle (int /*<<< orphan*/ ) ; 
 scalar_t__ ifmp_ring_is_stalled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iflib_if_qflush(if_t ifp)
{
	if_ctx_t ctx = if_getsoftc(ifp);
	iflib_txq_t txq = ctx->ifc_txqs;
	int i;

	STATE_LOCK(ctx);
	ctx->ifc_flags |= IFC_QFLUSH;
	STATE_UNLOCK(ctx);
	for (i = 0; i < NTXQSETS(ctx); i++, txq++)
		while (!(ifmp_ring_is_idle(txq->ift_br) || ifmp_ring_is_stalled(txq->ift_br)))
			iflib_txq_check_drain(txq, 0);
	STATE_LOCK(ctx);
	ctx->ifc_flags &= ~IFC_QFLUSH;
	STATE_UNLOCK(ctx);

	/*
	 * When ALTQ is enabled, this will also take care of purging the
	 * ALTQ queue(s).
	 */
	if_qflush(ifp);
}