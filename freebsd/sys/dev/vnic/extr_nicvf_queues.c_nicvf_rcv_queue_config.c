#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int qs_num; int rq_num; int cfg; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ rq; } ;
typedef  int uint64_t ;
struct rq_cfg {int ena; scalar_t__ tcp_ena; } ;
struct lro_ctrl {struct ifnet* ifp; } ;
struct rcv_queue {int enable; int cq_qs; int cq_idx; int start_rbdr_qs; int start_qs_rbdr_idx; int cont_rbdr_qs; int cont_qs_rbdr_idx; int caching; void* lro_enabled; struct lro_ctrl lro; } ;
struct queue_set {int vnic_id; int rbdr_cnt; struct rcv_queue* rq; } ;
struct nicvf {struct ifnet* ifp; int /*<<< orphan*/  dev; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 void* FALSE ; 
 int IFCAP_LRO ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_RQ_BP_CFG ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_RQ_CFG ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_RQ_DROP_CFG ; 
 int /*<<< orphan*/  NIC_QSET_RQ_0_7_CFG ; 
 int /*<<< orphan*/  NIC_QSET_RQ_GEN_CFG ; 
 int RQ_CQ_DROP ; 
 void* TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int if_getcapenable (struct ifnet*) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nicvf_reclaim_rcv_queue (struct nicvf*,struct queue_set*,int) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 
 int /*<<< orphan*/  tcp_lro_free (struct lro_ctrl*) ; 
 scalar_t__ tcp_lro_init (struct lro_ctrl*) ; 

__attribute__((used)) static void
nicvf_rcv_queue_config(struct nicvf *nic, struct queue_set *qs,
    int qidx, bool enable)
{
	union nic_mbx mbx = {};
	struct rcv_queue *rq;
	struct rq_cfg rq_cfg;
	struct ifnet *ifp;
	struct lro_ctrl	*lro;

	ifp = nic->ifp;

	rq = &qs->rq[qidx];
	rq->enable = enable;

	lro = &rq->lro;

	/* Disable receive queue */
	nicvf_queue_reg_write(nic, NIC_QSET_RQ_0_7_CFG, qidx, 0);

	if (!rq->enable) {
		nicvf_reclaim_rcv_queue(nic, qs, qidx);
		/* Free LRO memory */
		tcp_lro_free(lro);
		rq->lro_enabled = FALSE;
		return;
	}

	/* Configure LRO if enabled */
	rq->lro_enabled = FALSE;
	if ((if_getcapenable(ifp) & IFCAP_LRO) != 0) {
		if (tcp_lro_init(lro) != 0) {
			device_printf(nic->dev,
			    "Failed to initialize LRO for RXQ%d\n", qidx);
		} else {
			rq->lro_enabled = TRUE;
			lro->ifp = nic->ifp;
		}
	}

	rq->cq_qs = qs->vnic_id;
	rq->cq_idx = qidx;
	rq->start_rbdr_qs = qs->vnic_id;
	rq->start_qs_rbdr_idx = qs->rbdr_cnt - 1;
	rq->cont_rbdr_qs = qs->vnic_id;
	rq->cont_qs_rbdr_idx = qs->rbdr_cnt - 1;
	/* all writes of RBDR data to be loaded into L2 Cache as well*/
	rq->caching = 1;

	/* Send a mailbox msg to PF to config RQ */
	mbx.rq.msg = NIC_MBOX_MSG_RQ_CFG;
	mbx.rq.qs_num = qs->vnic_id;
	mbx.rq.rq_num = qidx;
	mbx.rq.cfg = (rq->caching << 26) | (rq->cq_qs << 19) |
	    (rq->cq_idx << 16) | (rq->cont_rbdr_qs << 9) |
	    (rq->cont_qs_rbdr_idx << 8) | (rq->start_rbdr_qs << 1) |
	    (rq->start_qs_rbdr_idx);
	nicvf_send_msg_to_pf(nic, &mbx);

	mbx.rq.msg = NIC_MBOX_MSG_RQ_BP_CFG;
	mbx.rq.cfg = (1UL << 63) | (1UL << 62) | (qs->vnic_id << 0);
	nicvf_send_msg_to_pf(nic, &mbx);

	/*
	 * RQ drop config
	 * Enable CQ drop to reserve sufficient CQEs for all tx packets
	 */
	mbx.rq.msg = NIC_MBOX_MSG_RQ_DROP_CFG;
	mbx.rq.cfg = (1UL << 62) | (RQ_CQ_DROP << 8);
	nicvf_send_msg_to_pf(nic, &mbx);

	nicvf_queue_reg_write(nic, NIC_QSET_RQ_GEN_CFG, 0, 0x00);

	/* Enable Receive queue */
	rq_cfg.ena = 1;
	rq_cfg.tcp_ena = 0;
	nicvf_queue_reg_write(nic, NIC_QSET_RQ_0_7_CFG, qidx,
	    *(uint64_t *)&rq_cfg);
}