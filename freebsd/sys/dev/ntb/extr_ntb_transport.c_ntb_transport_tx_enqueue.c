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
struct ntb_transport_qp {int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_err_no_buf; int /*<<< orphan*/  link_is_up; } ;
struct ntb_queue_entry {unsigned int len; scalar_t__ flags; void* buf; void* cb_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,struct ntb_queue_entry*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  KTR_NTB ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_list_add (int /*<<< orphan*/ *,struct ntb_queue_entry*,int /*<<< orphan*/ *) ; 
 struct ntb_queue_entry* ntb_list_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntb_process_tx (struct ntb_transport_qp*,struct ntb_queue_entry*) ; 

int
ntb_transport_tx_enqueue(struct ntb_transport_qp *qp, void *cb, void *data,
    unsigned int len)
{
	struct ntb_queue_entry *entry;
	int rc;

	if (!qp->link_is_up || len == 0) {
		CTR0(KTR_NTB, "TX: link not up");
		return (EINVAL);
	}

	entry = ntb_list_rm(&qp->ntb_tx_free_q_lock, &qp->tx_free_q);
	if (entry == NULL) {
		CTR0(KTR_NTB, "TX: could not get entry from tx_free_q");
		qp->tx_err_no_buf++;
		return (EBUSY);
	}
	CTR1(KTR_NTB, "TX: got entry %p from tx_free_q", entry);

	entry->cb_data = cb;
	entry->buf = data;
	entry->len = len;
	entry->flags = 0;

	mtx_lock(&qp->tx_lock);
	rc = ntb_process_tx(qp, entry);
	mtx_unlock(&qp->tx_lock);
	if (rc != 0) {
		ntb_list_add(&qp->ntb_tx_free_q_lock, entry, &qp->tx_free_q);
		CTR1(KTR_NTB,
		    "TX: process_tx failed. Returning entry %p to tx_free_q",
		    entry);
	}
	return (rc);
}