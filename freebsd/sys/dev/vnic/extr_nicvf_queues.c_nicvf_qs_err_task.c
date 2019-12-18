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
typedef  int uint64_t ;
struct queue_set {int cq_cnt; int /*<<< orphan*/ * sq; } ;
struct nicvf {int /*<<< orphan*/  ifp; struct queue_set* qs; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int CQ_ERR_MASK ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  NICVF_INTR_CQ ; 
 int /*<<< orphan*/  NICVF_INTR_QS_ERR ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_STATUS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_cmp_queue_config (struct nicvf*,struct queue_set*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_cq_intr_handler (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_enable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_sq_disable (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_sq_enable (struct nicvf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nicvf_sq_free_used_descs (struct nicvf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
nicvf_qs_err_task(void *arg, int pending)
{
	struct nicvf *nic;
	struct queue_set *qs;
	int qidx;
	uint64_t status;
	boolean_t enable = TRUE;

	nic = (struct nicvf *)arg;
	qs = nic->qs;

	/* Deactivate network interface */
	if_setdrvflagbits(nic->ifp, IFF_DRV_OACTIVE, IFF_DRV_RUNNING);

	/* Check if it is CQ err */
	for (qidx = 0; qidx < qs->cq_cnt; qidx++) {
		status = nicvf_queue_reg_read(nic, NIC_QSET_CQ_0_7_STATUS,
		    qidx);
		if ((status & CQ_ERR_MASK) == 0)
			continue;
		/* Process already queued CQEs and reconfig CQ */
		nicvf_disable_intr(nic, NICVF_INTR_CQ, qidx);
		nicvf_sq_disable(nic, qidx);
		(void)nicvf_cq_intr_handler(nic, qidx);
		nicvf_cmp_queue_config(nic, qs, qidx, enable);
		nicvf_sq_free_used_descs(nic, &qs->sq[qidx], qidx);
		nicvf_sq_enable(nic, &qs->sq[qidx], qidx);
		nicvf_enable_intr(nic, NICVF_INTR_CQ, qidx);
	}

	if_setdrvflagbits(nic->ifp, IFF_DRV_RUNNING, IFF_DRV_OACTIVE);
	/* Re-enable Qset error interrupt */
	nicvf_enable_intr(nic, NICVF_INTR_QS_ERR, 0);
}