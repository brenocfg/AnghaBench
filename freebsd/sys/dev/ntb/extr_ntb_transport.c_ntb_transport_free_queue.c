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
struct ntb_transport_qp {unsigned long long qp_num; int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  rx_post_q; int /*<<< orphan*/  ntb_rx_q_lock; int /*<<< orphan*/  rx_pend_q; int /*<<< orphan*/ * event_handler; int /*<<< orphan*/ * tx_handler; int /*<<< orphan*/ * rx_handler; int /*<<< orphan*/ * cb_data; int /*<<< orphan*/  rxc_tq; int /*<<< orphan*/  dev; int /*<<< orphan*/  link_work; struct ntb_transport_ctx* transport; } ;
struct ntb_transport_ctx {int qp_bitmap; } ;
struct ntb_queue_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NTB_T ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ntb_queue_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_set_mask (int /*<<< orphan*/ ,unsigned long long) ; 
 struct ntb_queue_entry* ntb_list_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

void
ntb_transport_free_queue(struct ntb_transport_qp *qp)
{
	struct ntb_transport_ctx *nt = qp->transport;
	struct ntb_queue_entry *entry;

	callout_drain(&qp->link_work);

	ntb_db_set_mask(qp->dev, 1ull << qp->qp_num);
	taskqueue_drain_all(qp->rxc_tq);
	taskqueue_free(qp->rxc_tq);

	qp->cb_data = NULL;
	qp->rx_handler = NULL;
	qp->tx_handler = NULL;
	qp->event_handler = NULL;

	while ((entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_pend_q)))
		free(entry, M_NTB_T);

	while ((entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_post_q)))
		free(entry, M_NTB_T);

	while ((entry = ntb_list_rm(&qp->ntb_tx_free_q_lock, &qp->tx_free_q)))
		free(entry, M_NTB_T);

	nt->qp_bitmap &= ~(1 << qp->qp_num);
}