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
struct ntb_transport_qp {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  link_is_up; } ;
struct ntb_queue_entry {int /*<<< orphan*/  flags; scalar_t__ len; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * cb_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTBT_LINK_DOWN_FLAG ; 
 int NTB_LINK_DOWN_TIMEOUT ; 
 int hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct ntb_queue_entry* ntb_list_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntb_process_tx (struct ntb_transport_qp*,struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  ntb_qp_link_down_reset (struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
ntb_send_link_down(struct ntb_transport_qp *qp)
{
	struct ntb_queue_entry *entry;
	int i, rc;

	if (!qp->link_is_up)
		return;

	for (i = 0; i < NTB_LINK_DOWN_TIMEOUT; i++) {
		entry = ntb_list_rm(&qp->ntb_tx_free_q_lock, &qp->tx_free_q);
		if (entry != NULL)
			break;
		pause("NTB Wait for link down", hz / 10);
	}

	if (entry == NULL)
		return;

	entry->cb_data = NULL;
	entry->buf = NULL;
	entry->len = 0;
	entry->flags = NTBT_LINK_DOWN_FLAG;

	mtx_lock(&qp->tx_lock);
	rc = ntb_process_tx(qp, entry);
	mtx_unlock(&qp->tx_lock);
	if (rc != 0)
		printf("ntb: Failed to send link down\n");

	ntb_qp_link_down_reset(qp);
}