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
struct ib_qp {int /*<<< orphan*/  qp_num; } ;
struct qlnxr_qp {struct ib_qp ibqp; int /*<<< orphan*/  qp_id; } ;
struct qlnxr_pd {int dummy; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_init_attr {scalar_t__ qp_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  event_handler; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_2__ {int /*<<< orphan*/  icid; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 struct ib_qp* ERR_PTR (int) ; 
 scalar_t__ IB_QPT_GSI ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* get_qlnxr_cq (int /*<<< orphan*/ ) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_pd* get_qlnxr_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_qp*) ; 
 struct qlnxr_qp* qlnx_zalloc (int) ; 
 int qlnxr_check_qp_attrs (struct ib_pd*,struct qlnxr_dev*,struct ib_qp_init_attr*,struct ib_udata*) ; 
 struct ib_qp* qlnxr_create_gsi_qp (struct qlnxr_dev*,struct ib_qp_init_attr*,struct qlnxr_qp*) ; 
 int qlnxr_create_kernel_qp (struct qlnxr_dev*,struct qlnxr_qp*,struct ib_pd*,struct ib_qp_init_attr*) ; 
 int qlnxr_create_user_qp (struct qlnxr_dev*,struct qlnxr_qp*,struct ib_pd*,struct ib_udata*,struct ib_qp_init_attr*) ; 
 int qlnxr_idr_add (struct qlnxr_dev*,struct qlnxr_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_set_common_qp_params (struct qlnxr_dev*,struct qlnxr_qp*,struct qlnxr_pd*,struct ib_qp_init_attr*) ; 

struct ib_qp *
qlnxr_create_qp(struct ib_pd *ibpd,
		struct ib_qp_init_attr *attrs,
		struct ib_udata *udata)
{
	struct qlnxr_dev *dev = get_qlnxr_dev(ibpd->device);
	struct qlnxr_pd *pd = get_qlnxr_pd(ibpd);
	struct qlnxr_qp *qp;
	int rc = 0;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	rc = qlnxr_check_qp_attrs(ibpd, dev, attrs, udata);
	if (rc) {
		QL_DPRINT11(ha, "qlnxr_check_qp_attrs failed [%d]\n", rc);
		return ERR_PTR(rc);
	}

	QL_DPRINT12(ha, "called from %s, event_handle=%p,"
		" eepd=%p sq_cq=%p, sq_icid=%d, rq_cq=%p, rq_icid=%d\n",
		(udata ? "user library" : "kernel"),
		attrs->event_handler, pd,
		get_qlnxr_cq(attrs->send_cq),
		get_qlnxr_cq(attrs->send_cq)->icid,
		get_qlnxr_cq(attrs->recv_cq),
		get_qlnxr_cq(attrs->recv_cq)->icid);

	qp = qlnx_zalloc(sizeof(struct qlnxr_qp));

	if (!qp) {
		QL_DPRINT11(ha, "kzalloc(qp) failed\n");
		return ERR_PTR(-ENOMEM);
	}

	qlnxr_set_common_qp_params(dev, qp, pd, attrs);

	if (attrs->qp_type == IB_QPT_GSI) {
		QL_DPRINT11(ha, "calling qlnxr_create_gsi_qp\n");
		return qlnxr_create_gsi_qp(dev, attrs, qp);
	}

	if (udata) {
		rc = qlnxr_create_user_qp(dev, qp, ibpd, udata, attrs);

		if (rc) {
			QL_DPRINT11(ha, "qlnxr_create_user_qp failed\n");
			goto err;
		}
	} else {
		rc = qlnxr_create_kernel_qp(dev, qp, ibpd, attrs);

		if (rc) {
			QL_DPRINT11(ha, "qlnxr_create_kernel_qp failed\n");
			goto err;
		}
	}

	qp->ibqp.qp_num = qp->qp_id;

	rc = qlnxr_idr_add(dev, qp, qp->qp_id);

	if (rc) {
		QL_DPRINT11(ha, "qlnxr_idr_add failed\n");
		goto err;
	}

	QL_DPRINT12(ha, "exit [%p]\n", &qp->ibqp);

	return &qp->ibqp;
err:
	kfree(qp);

	QL_DPRINT12(ha, "failed exit\n");
	return ERR_PTR(-EFAULT);
}