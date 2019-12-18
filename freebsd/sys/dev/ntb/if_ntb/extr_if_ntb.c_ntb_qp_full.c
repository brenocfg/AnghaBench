#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ntb_net_queue {int /*<<< orphan*/  queue_full; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  tx_tq; int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KTR_NTB ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  callout_schedule_sbt (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ntb_transport_tx_free_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ntb_qp_full(void *arg)
{
	struct ntb_net_queue *q = arg;

	CTR0(KTR_NTB, "TX: qp_full callout");
	if (ntb_transport_tx_free_entry(q->qp) > 0)
		taskqueue_enqueue(q->tx_tq, &q->tx_task);
	else
		callout_schedule_sbt(&q->queue_full,
		    SBT_1MS / 4, SBT_1MS / 4, 0);
}