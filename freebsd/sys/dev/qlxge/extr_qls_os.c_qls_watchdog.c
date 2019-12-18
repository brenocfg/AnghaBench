#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ifq_head; } ;
struct ifnet {TYPE_2__ if_snd; } ;
struct TYPE_5__ {int /*<<< orphan*/  qla_watchdog_pause; scalar_t__ qla_watchdog_exit; } ;
struct TYPE_7__ {int qla_watchdog_exited; int qla_watchdog_paused; int watchdog_ticks; int /*<<< orphan*/  tx_callout; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  tx_tq; int /*<<< orphan*/  err_task; int /*<<< orphan*/  err_tq; scalar_t__ err_inject; scalar_t__ qla_initiate_recovery; TYPE_1__ flags; struct ifnet* ifp; } ;
typedef  TYPE_3__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_WATCHDOG_CALLOUT_TICKS ; 
 scalar_t__ QL_RUNNING (struct ifnet*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_3__*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qls_watchdog(void *arg)
{
	qla_host_t *ha = arg;
	struct ifnet *ifp;

	ifp = ha->ifp;

        if (ha->flags.qla_watchdog_exit) {
		ha->qla_watchdog_exited = 1;
		return;
	}
	ha->qla_watchdog_exited = 0;

	if (!ha->flags.qla_watchdog_pause) {

		if (ha->qla_initiate_recovery) {

			ha->qla_watchdog_paused = 1;
			ha->qla_initiate_recovery = 0;
			ha->err_inject = 0;
			taskqueue_enqueue(ha->err_tq, &ha->err_task);

		} else if ((ifp->if_snd.ifq_head != NULL) && QL_RUNNING(ifp)) {

			taskqueue_enqueue(ha->tx_tq, &ha->tx_task);
		}

		ha->qla_watchdog_paused = 0;
	} else {
		ha->qla_watchdog_paused = 1;
	}

	ha->watchdog_ticks = ha->watchdog_ticks++ % 1000;
	callout_reset(&ha->tx_callout, QLA_WATCHDOG_CALLOUT_TICKS,
		qls_watchdog, ha);

	return;
}