#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  TYPE_1__* iflib_rxq_t ;
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_7__ {int ifc_sysctl_rx_budget; int ifc_flags; int /*<<< orphan*/  ifc_ifp; } ;
struct TYPE_6__ {int /*<<< orphan*/  ifr_task; int /*<<< orphan*/  ifr_id; int /*<<< orphan*/ * ifr_cpu_exec_count; TYPE_2__* ifr_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GROUPTASK_ENQUEUE (int /*<<< orphan*/ *) ; 
 int IFCAP_NETMAP ; 
 int IFC_LEGACY ; 
 int /*<<< orphan*/  IFDI_INTR_ENABLE (TYPE_2__*) ; 
 int /*<<< orphan*/  IFDI_RX_QUEUE_INTR_ENABLE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ __predict_false (int) ; 
 size_t curcpu ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int iflib_rxeof (TYPE_1__*,int) ; 
 scalar_t__ netmap_rx_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_intr_enables ; 
 int /*<<< orphan*/  task_fn_rxs ; 

__attribute__((used)) static void
_task_fn_rx(void *context)
{
	iflib_rxq_t rxq = context;
	if_ctx_t ctx = rxq->ifr_ctx;
	bool more;
	uint16_t budget;

#ifdef IFLIB_DIAGNOSTICS
	rxq->ifr_cpu_exec_count[curcpu]++;
#endif
	DBG_COUNTER_INC(task_fn_rxs);
	if (__predict_false(!(if_getdrvflags(ctx->ifc_ifp) & IFF_DRV_RUNNING)))
		return;
	more = true;
#ifdef DEV_NETMAP
	if (if_getcapenable(ctx->ifc_ifp) & IFCAP_NETMAP) {
		u_int work = 0;
		if (netmap_rx_irq(ctx->ifc_ifp, rxq->ifr_id, &work)) {
			more = false;
		}
	}
#endif
	budget = ctx->ifc_sysctl_rx_budget;
	if (budget == 0)
		budget = 16;	/* XXX */
	if (more == false || (more = iflib_rxeof(rxq, budget)) == false) {
		if (ctx->ifc_flags & IFC_LEGACY)
			IFDI_INTR_ENABLE(ctx);
		else
			IFDI_RX_QUEUE_INTR_ENABLE(ctx, rxq->ifr_id);
		DBG_COUNTER_INC(rx_intr_enables);
	}
	if (__predict_false(!(if_getdrvflags(ctx->ifc_ifp) & IFF_DRV_RUNNING)))
		return;
	if (more)
		GROUPTASK_ENQUEUE(&rxq->ifr_task);
}