#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ifq_head; } ;
struct ifnet {TYPE_2__ if_snd; } ;
struct TYPE_8__ {scalar_t__ txr_comp; int /*<<< orphan*/ * tx_cons; } ;
typedef  TYPE_3__ qla_hw_t ;
struct TYPE_6__ {int /*<<< orphan*/  qla_watchdog_pause; scalar_t__ qla_watchdog_exit; } ;
struct TYPE_9__ {int watchdog_ticks; int /*<<< orphan*/  tx_callout; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  tx_tq; TYPE_1__ flags; struct ifnet* ifp; TYPE_3__ hw; } ;
typedef  TYPE_4__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_WATCHDOG_CALLOUT_TICKS ; 
 scalar_t__ QL_RUNNING (struct ifnet*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_4__*) ; 
 scalar_t__ qla_le32_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla_watchdog(void *arg)
{
	qla_host_t *ha = arg;
	qla_hw_t *hw;
	struct ifnet *ifp;

	hw = &ha->hw;
	ifp = ha->ifp;

        if (ha->flags.qla_watchdog_exit)
		return;

	if (!ha->flags.qla_watchdog_pause) {
		if (qla_le32_to_host(*(hw->tx_cons)) != hw->txr_comp) {
			taskqueue_enqueue(ha->tx_tq, &ha->tx_task);
		} else if ((ifp->if_snd.ifq_head != NULL) && QL_RUNNING(ifp)) {
			taskqueue_enqueue(ha->tx_tq, &ha->tx_task);
		}
	}
	ha->watchdog_ticks = ha->watchdog_ticks++ % 1000;
	callout_reset(&ha->tx_callout, QLA_WATCHDOG_CALLOUT_TICKS,
		qla_watchdog, ha);
}