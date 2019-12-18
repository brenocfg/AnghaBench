#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ib_qp {int qp_num; } ;
struct TYPE_9__ {int max_wr; } ;
struct TYPE_8__ {int max_wr; } ;
struct qlnxr_qp {void* rqe_wr_id; struct ib_qp ibqp; void* wqe_wr_id; TYPE_3__ sq; TYPE_2__ rq; } ;
struct qlnxr_dev {TYPE_5__* ha; TYPE_4__* gsi_rqcq; int /*<<< orphan*/  gsi_ll2_mac_address; } ;
struct TYPE_7__ {int max_recv_wr; int max_send_wr; } ;
struct ib_qp_init_attr {TYPE_1__ cap; } ;
struct TYPE_11__ {int /*<<< orphan*/  primary_mac; } ;
struct TYPE_10__ {void* cq_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_qp* ERR_PTR (int) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* QLNXR_CQ_TYPE_GSI ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlnxr_check_gsi_qp_attrs (struct qlnxr_dev*,struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  qlnxr_destroy_gsi_cq (struct qlnxr_dev*,struct ib_qp_init_attr*) ; 
 int qlnxr_ll2_start (struct qlnxr_dev*,struct ib_qp_init_attr*,struct qlnxr_qp*) ; 
 int qlnxr_ll2_stop (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  qlnxr_store_gsi_qp_cq (struct qlnxr_dev*,struct qlnxr_qp*,struct ib_qp_init_attr*) ; 

struct ib_qp*
qlnxr_create_gsi_qp(struct qlnxr_dev *dev,
		 struct ib_qp_init_attr *attrs,
		 struct qlnxr_qp *qp)
{
	int rc;

	QL_DPRINT12(dev->ha, "enter\n");

	rc = qlnxr_check_gsi_qp_attrs(dev, attrs);

	if (rc) {
		QL_DPRINT11(dev->ha, "qlnxr_check_gsi_qp_attrs failed\n");
		return ERR_PTR(rc);
	}

	rc = qlnxr_ll2_start(dev, attrs, qp);
	if (rc) {
		QL_DPRINT11(dev->ha, "qlnxr_ll2_start failed\n");
		return ERR_PTR(rc);
	}

	/* create QP */
	qp->ibqp.qp_num = 1;
	qp->rq.max_wr = attrs->cap.max_recv_wr;
	qp->sq.max_wr = attrs->cap.max_send_wr;

	qp->rqe_wr_id = kzalloc(qp->rq.max_wr * sizeof(*qp->rqe_wr_id),
				GFP_KERNEL);
	if (!qp->rqe_wr_id) {
		QL_DPRINT11(dev->ha, "(!qp->rqe_wr_id)\n");
		goto err;
	}

	qp->wqe_wr_id = kzalloc(qp->sq.max_wr * sizeof(*qp->wqe_wr_id),
				GFP_KERNEL);
	if (!qp->wqe_wr_id) {
		QL_DPRINT11(dev->ha, "(!qp->wqe_wr_id)\n");
		goto err;
	}

	qlnxr_store_gsi_qp_cq(dev, qp, attrs);
	memcpy(dev->gsi_ll2_mac_address, dev->ha->primary_mac, ETH_ALEN);

	/* the GSI CQ is handled by the driver so remove it from the FW */
	qlnxr_destroy_gsi_cq(dev, attrs);
	dev->gsi_rqcq->cq_type = QLNXR_CQ_TYPE_GSI;
	dev->gsi_rqcq->cq_type = QLNXR_CQ_TYPE_GSI;

	QL_DPRINT12(dev->ha, "exit &qp->ibqp = %p\n", &qp->ibqp);

	return &qp->ibqp;
err:
	kfree(qp->rqe_wr_id);

	rc = qlnxr_ll2_stop(dev);

	QL_DPRINT12(dev->ha, "exit with error\n");

	return ERR_PTR(-ENOMEM);
}