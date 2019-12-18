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
struct TYPE_3__ {int qs_num; int sq_num; int cfg; int /*<<< orphan*/  sqs_mode; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ sq; } ;
typedef  int /*<<< orphan*/  uint64_t ;
struct sq_cfg {int ena; scalar_t__ tstmp_bgx_intf; int /*<<< orphan*/  qsize; scalar_t__ ldwb; scalar_t__ reset; } ;
struct TYPE_4__ {scalar_t__ phys_base; } ;
struct snd_queue {int cq_qs; int cq_idx; int /*<<< orphan*/  thresh; TYPE_2__ dmem; int /*<<< orphan*/  enable; } ;
struct queue_set {int vnic_id; struct snd_queue* sq; } ;
struct nicvf {int /*<<< orphan*/  sqs_mode; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  NICVF_SQ_RESET ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_SQ_CFG ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_BASE ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_CFG ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_THRESH ; 
 int /*<<< orphan*/  SND_QSIZE ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_reclaim_snd_queue (struct nicvf*,struct queue_set*,int) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void
nicvf_snd_queue_config(struct nicvf *nic, struct queue_set *qs, int qidx,
    boolean_t enable)
{
	union nic_mbx mbx = {};
	struct snd_queue *sq;
	struct sq_cfg sq_cfg;

	sq = &qs->sq[qidx];
	sq->enable = enable;

	if (!sq->enable) {
		nicvf_reclaim_snd_queue(nic, qs, qidx);
		return;
	}

	/* Reset send queue */
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_CFG, qidx, NICVF_SQ_RESET);

	sq->cq_qs = qs->vnic_id;
	sq->cq_idx = qidx;

	/* Send a mailbox msg to PF to config SQ */
	mbx.sq.msg = NIC_MBOX_MSG_SQ_CFG;
	mbx.sq.qs_num = qs->vnic_id;
	mbx.sq.sq_num = qidx;
	mbx.sq.sqs_mode = nic->sqs_mode;
	mbx.sq.cfg = (sq->cq_qs << 3) | sq->cq_idx;
	nicvf_send_msg_to_pf(nic, &mbx);

	/* Set queue base address */
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_BASE, qidx,
	    (uint64_t)(sq->dmem.phys_base));

	/* Enable send queue  & set queue size */
	sq_cfg.ena = 1;
	sq_cfg.reset = 0;
	sq_cfg.ldwb = 0;
	sq_cfg.qsize = SND_QSIZE;
	sq_cfg.tstmp_bgx_intf = 0;
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_CFG, qidx, *(uint64_t *)&sq_cfg);

	/* Set threshold value for interrupt generation */
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_THRESH, qidx, sq->thresh);
}