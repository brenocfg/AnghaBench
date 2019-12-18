#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ntb_transport_qp {int /*<<< orphan*/  ntb_rx_q_lock; int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* rx_handler ) (struct ntb_transport_qp*,int /*<<< orphan*/ ,struct mbuf*,unsigned int) ;scalar_t__ client_ready; int /*<<< orphan*/  rx_pend_q; int /*<<< orphan*/  rx_post_q; TYPE_2__* rx_info; } ;
struct ntb_queue_entry {int flags; unsigned int len; int /*<<< orphan*/  cb_data; struct mbuf* buf; int /*<<< orphan*/  index; TYPE_1__* x_hdr; } ;
struct mbuf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry; } ;
struct TYPE_3__ {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct ntb_queue_entry*,struct mbuf*) ; 
 int /*<<< orphan*/  KTR_NTB ; 
 int NTBT_DESC_DONE_FLAG ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ntb_queue_entry* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ntb_queue_entry*,struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ntb_transport_qp*,int /*<<< orphan*/ ,struct mbuf*,unsigned int) ; 
 unsigned int transport_mtu ; 

__attribute__((used)) static void
ntb_complete_rxc(struct ntb_transport_qp *qp)
{
	struct ntb_queue_entry *entry;
	struct mbuf *m;
	unsigned len;

	CTR0(KTR_NTB, "RX: rx_completion_task");

	mtx_lock_spin(&qp->ntb_rx_q_lock);

	while (!STAILQ_EMPTY(&qp->rx_post_q)) {
		entry = STAILQ_FIRST(&qp->rx_post_q);
		if ((entry->flags & NTBT_DESC_DONE_FLAG) == 0)
			break;

		entry->x_hdr->flags = 0;
		iowrite32(entry->index, &qp->rx_info->entry);

		STAILQ_REMOVE_HEAD(&qp->rx_post_q, entry);

		len = entry->len;
		m = entry->buf;

		/*
		 * Re-initialize queue_entry for reuse; rx_handler takes
		 * ownership of the mbuf.
		 */
		entry->buf = NULL;
		entry->len = transport_mtu;
		entry->cb_data = qp->cb_data;

		STAILQ_INSERT_TAIL(&qp->rx_pend_q, entry, entry);

		mtx_unlock_spin(&qp->ntb_rx_q_lock);

		CTR2(KTR_NTB, "RX: completing entry %p, mbuf %p", entry, m);
		if (qp->rx_handler != NULL && qp->client_ready)
			qp->rx_handler(qp, qp->cb_data, m, len);
		else
			m_freem(m);

		mtx_lock_spin(&qp->ntb_rx_q_lock);
	}

	mtx_unlock_spin(&qp->ntb_rx_q_lock);
}