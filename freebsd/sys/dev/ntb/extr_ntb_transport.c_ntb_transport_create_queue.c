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
struct ntb_transport_qp {int qp_num; int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  rx_pend_q; int /*<<< orphan*/  ntb_rx_q_lock; int /*<<< orphan*/  event_handler; int /*<<< orphan*/  tx_handler; int /*<<< orphan*/  rx_handler; void* cb_data; } ;
struct ntb_transport_ctx {int qp_bitmap; struct ntb_transport_qp* qp_vec; } ;
struct ntb_transport_child {int qpcnt; int qpoff; } ;
struct ntb_queue_handlers {int /*<<< orphan*/  event_handler; int /*<<< orphan*/  tx_handler; int /*<<< orphan*/  rx_handler; } ;
struct ntb_queue_entry {struct ntb_transport_qp* qp; int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; void* cb_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NTB_T ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NTB_QP_DEF_NUM_ENTRIES ; 
 struct ntb_transport_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ntb_transport_ctx* device_get_softc (int /*<<< orphan*/ ) ; 
 struct ntb_queue_entry* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntb_db_clear (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ntb_list_add (int /*<<< orphan*/ *,struct ntb_queue_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_mtu ; 

struct ntb_transport_qp *
ntb_transport_create_queue(device_t dev, int q,
    const struct ntb_queue_handlers *handlers, void *data)
{
	struct ntb_transport_child *nc = device_get_ivars(dev);
	struct ntb_transport_ctx *nt = device_get_softc(device_get_parent(dev));
	struct ntb_queue_entry *entry;
	struct ntb_transport_qp *qp;
	int i;

	if (q < 0 || q >= nc->qpcnt)
		return (NULL);

	qp = &nt->qp_vec[nc->qpoff + q];
	nt->qp_bitmap |= (1 << qp->qp_num);
	qp->cb_data = data;
	qp->rx_handler = handlers->rx_handler;
	qp->tx_handler = handlers->tx_handler;
	qp->event_handler = handlers->event_handler;

	for (i = 0; i < NTB_QP_DEF_NUM_ENTRIES; i++) {
		entry = malloc(sizeof(*entry), M_NTB_T, M_WAITOK | M_ZERO);
		entry->cb_data = data;
		entry->buf = NULL;
		entry->len = transport_mtu;
		entry->qp = qp;
		ntb_list_add(&qp->ntb_rx_q_lock, entry, &qp->rx_pend_q);
	}

	for (i = 0; i < NTB_QP_DEF_NUM_ENTRIES; i++) {
		entry = malloc(sizeof(*entry), M_NTB_T, M_WAITOK | M_ZERO);
		entry->qp = qp;
		ntb_list_add(&qp->ntb_tx_free_q_lock, entry, &qp->tx_free_q);
	}

	ntb_db_clear(dev, 1ull << qp->qp_num);
	return (qp);
}