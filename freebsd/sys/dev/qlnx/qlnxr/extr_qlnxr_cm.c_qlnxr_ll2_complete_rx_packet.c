#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_12__ {size_t gsi_cons; } ;
struct qlnxr_qp {int /*<<< orphan*/  q_lock; TYPE_6__ rq; TYPE_4__* rqe_wr_id; } ;
struct qlnxr_dev {int /*<<< orphan*/  ha; struct qlnxr_qp* gsi_qp; struct qlnxr_cq* gsi_rqcq; } ;
struct TYPE_11__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct qlnxr_cq {TYPE_5__ ibcq; } ;
struct TYPE_9__ {int /*<<< orphan*/  data_length; } ;
struct TYPE_7__ {scalar_t__ data_length_error; } ;
struct ecore_ll2_comp_rx_data {int qp_id; scalar_t__ opaque_data_1; int /*<<< orphan*/  opaque_data_0; TYPE_3__ length; int /*<<< orphan*/  vlan; TYPE_1__ u; int /*<<< orphan*/  rx_buf_addr; int /*<<< orphan*/ * cookie; } ;
struct TYPE_10__ {int /*<<< orphan*/ * smac; TYPE_2__* sg_list; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  rc; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_inc_sw_gsi_cons (TYPE_6__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 

void
qlnxr_ll2_complete_rx_packet(void *cxt,
		struct ecore_ll2_comp_rx_data *data)
{
	struct qlnxr_dev *dev = (struct qlnxr_dev *)cxt;
	struct qlnxr_cq *cq = dev->gsi_rqcq;
	// struct qlnxr_qp *qp = dev->gsi_qp;
	struct qlnxr_qp *qp = NULL;
	unsigned long flags;
	uint32_t qp_num = 0;
	// uint32_t delay_count = 0, gsi_cons = 0;
	//void * dest_va;

	QL_DPRINT12(dev->ha, "enter\n");

	if (data->u.data_length_error) {
		/* TODO: add statistic */
	}

	if (data->cookie == NULL) {
		QL_DPRINT12(dev->ha, "cookie is NULL, bad sign\n");
	}

	qp_num = (0xFF << 16) | data->qp_id;

	if (data->qp_id == 1) {
		qp = dev->gsi_qp;
	} else {
		/* TODO: This will be needed for UD QP support */
		/* For RoCEv1 this is invalid */
		QL_DPRINT12(dev->ha, "invalid QP\n");
		return;
	}
	/* note: currently only one recv sg is supported */
	QL_DPRINT12(dev->ha, "MAD received on QP : %x\n", data->rx_buf_addr);

	spin_lock_irqsave(&qp->q_lock, flags);

	qp->rqe_wr_id[qp->rq.gsi_cons].rc =
		data->u.data_length_error ? -EINVAL : 0;
	qp->rqe_wr_id[qp->rq.gsi_cons].vlan_id = data->vlan;
	/* note: length stands for data length i.e. GRH is excluded */
	qp->rqe_wr_id[qp->rq.gsi_cons].sg_list[0].length =
		data->length.data_length;
	*((u32 *)&qp->rqe_wr_id[qp->rq.gsi_cons].smac[0]) =
		ntohl(data->opaque_data_0);
	*((u16 *)&qp->rqe_wr_id[qp->rq.gsi_cons].smac[4]) =
		ntohs((u16)data->opaque_data_1);

	qlnxr_inc_sw_gsi_cons(&qp->rq);

	spin_unlock_irqrestore(&qp->q_lock, flags);

	if (cq->ibcq.comp_handler)
		(*cq->ibcq.comp_handler) (&cq->ibcq, cq->ibcq.cq_context);

	QL_DPRINT12(dev->ha, "exit\n");

	return;
}