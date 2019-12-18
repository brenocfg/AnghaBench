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
typedef  scalar_t__ vm_paddr_t ;
typedef  size_t uint64_t ;
struct ntb_transport_qp {unsigned int qp_num; int client_ready; scalar_t__ tx_mw_phys; size_t tx_max_frame; size_t tx_max_entry; int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  rx_pend_q; int /*<<< orphan*/  rx_post_q; int /*<<< orphan*/  rxc_tq; int /*<<< orphan*/  rxc_db_work; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  ntb_rx_q_lock; int /*<<< orphan*/  rx_full; int /*<<< orphan*/  link_work; int /*<<< orphan*/ * tx_mw; void* rx_info; int /*<<< orphan*/ * event_handler; int /*<<< orphan*/  dev; struct ntb_transport_ctx* transport; } ;
struct ntb_transport_mw {scalar_t__ phys_addr; unsigned int tx_size; int /*<<< orphan*/ * vbase; } ;
struct ntb_transport_ctx {unsigned int mw_count; unsigned int qp_count; int /*<<< orphan*/  dev; struct ntb_transport_qp* qp_vec; struct ntb_transport_mw* mw_vec; } ;
struct ntb_rx_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PI_NET ; 
 unsigned int QP_TO_MW (struct ntb_transport_ctx*,unsigned int) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_qp_link_down_reset (struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  ntb_transport_rxc_db ; 
 size_t qmin (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  transport_mtu ; 

__attribute__((used)) static void
ntb_transport_init_queue(struct ntb_transport_ctx *nt, unsigned int qp_num)
{
	struct ntb_transport_mw *mw;
	struct ntb_transport_qp *qp;
	vm_paddr_t mw_base;
	uint64_t qp_offset;
	size_t tx_size;
	unsigned num_qps_mw, mw_num, mw_count;

	mw_count = nt->mw_count;
	mw_num = QP_TO_MW(nt, qp_num);
	mw = &nt->mw_vec[mw_num];

	qp = &nt->qp_vec[qp_num];
	qp->qp_num = qp_num;
	qp->transport = nt;
	qp->dev = nt->dev;
	qp->client_ready = false;
	qp->event_handler = NULL;
	ntb_qp_link_down_reset(qp);

	if (mw_num < nt->qp_count % mw_count)
		num_qps_mw = nt->qp_count / mw_count + 1;
	else
		num_qps_mw = nt->qp_count / mw_count;

	mw_base = mw->phys_addr;

	tx_size = mw->tx_size / num_qps_mw;
	qp_offset = tx_size * (qp_num / mw_count);

	qp->tx_mw = mw->vbase + qp_offset;
	KASSERT(qp->tx_mw != NULL, ("uh oh?"));

	/* XXX Assumes that a vm_paddr_t is equivalent to bus_addr_t */
	qp->tx_mw_phys = mw_base + qp_offset;
	KASSERT(qp->tx_mw_phys != 0, ("uh oh?"));

	tx_size -= sizeof(struct ntb_rx_info);
	qp->rx_info = (void *)(qp->tx_mw + tx_size);

	/* Due to house-keeping, there must be at least 2 buffs */
	qp->tx_max_frame = qmin(transport_mtu, tx_size / 2);
	qp->tx_max_entry = tx_size / qp->tx_max_frame;

	callout_init(&qp->link_work, 0);
	callout_init(&qp->rx_full, 1);

	mtx_init(&qp->ntb_rx_q_lock, "ntb rx q", NULL, MTX_SPIN);
	mtx_init(&qp->ntb_tx_free_q_lock, "ntb tx free q", NULL, MTX_SPIN);
	mtx_init(&qp->tx_lock, "ntb transport tx", NULL, MTX_DEF);
	TASK_INIT(&qp->rxc_db_work, 0, ntb_transport_rxc_db, qp);
	qp->rxc_tq = taskqueue_create("ntbt_rx", M_WAITOK,
	    taskqueue_thread_enqueue, &qp->rxc_tq);
	taskqueue_start_threads(&qp->rxc_tq, 1, PI_NET, "%s rx%d",
	    device_get_nameunit(nt->dev), qp_num);

	STAILQ_INIT(&qp->rx_post_q);
	STAILQ_INIT(&qp->rx_pend_q);
	STAILQ_INIT(&qp->tx_free_q);
}