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
struct qlnxr_dev {scalar_t__ gsi_qp_created; int /*<<< orphan*/ * ha; int /*<<< orphan*/  rdma_ctx; } ;
struct qlnxr_cq {scalar_t__ cq_type; } ;
struct ib_udata {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  qpg_tss_mask_sz; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_type; TYPE_2__ cap; scalar_t__ srq; int /*<<< orphan*/  port_num; int /*<<< orphan*/  qpg_type; int /*<<< orphan*/  create_flags; int /*<<< orphan*/  sq_sig_type; } ;
struct ib_pd {TYPE_1__* uobject; } ;
struct ecore_rdma_device {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_inline; int /*<<< orphan*/  max_wqe; int /*<<< orphan*/  bad_pkey_counter; int /*<<< orphan*/  reserved_lkey; int /*<<< orphan*/  dev_ack_delay; scalar_t__ page_size_caps; int /*<<< orphan*/  max_stats_queues; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_pkey; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_pd; scalar_t__ max_mr_mw_fmr_size; int /*<<< orphan*/  max_mr_mw_fmr_pbl; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_cqe; scalar_t__ max_mr_size; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_dev_resp_rd_atomic_resc; int /*<<< orphan*/  max_qp_req_rd_atomic_resc; int /*<<< orphan*/  max_qp_resp_rd_atomic_resc; int /*<<< orphan*/  max_srq_wqe; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_cnq; scalar_t__ sys_image_guid; scalar_t__ node_guid; scalar_t__ fw_ver; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_3__ {scalar_t__ context; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 scalar_t__ QLNXR_CQ_TYPE_GSI ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 struct ecore_rdma_device* ecore_rdma_query_device (int /*<<< orphan*/ ) ; 
 struct qlnxr_cq* get_qlnxr_cq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnxr_check_qp_attrs(struct ib_pd *ibpd,
	struct qlnxr_dev *dev,
	struct ib_qp_init_attr *attrs,
	struct ib_udata *udata)
{
	struct ecore_rdma_device	*qattr;
	qlnx_host_t			*ha;

	qattr = ecore_rdma_query_device(dev->rdma_ctx);
	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	QL_DPRINT12(ha, "attrs->sq_sig_type = %d\n", attrs->sq_sig_type);
	QL_DPRINT12(ha, "attrs->qp_type = %d\n", attrs->qp_type);
	QL_DPRINT12(ha, "attrs->create_flags = %d\n", attrs->create_flags);

#if __FreeBSD_version < 1102000
	QL_DPRINT12(ha, "attrs->qpg_type = %d\n", attrs->qpg_type);
#endif

	QL_DPRINT12(ha, "attrs->port_num = %d\n", attrs->port_num);
	QL_DPRINT12(ha, "attrs->cap.max_send_wr = 0x%x\n", attrs->cap.max_send_wr);
	QL_DPRINT12(ha, "attrs->cap.max_recv_wr = 0x%x\n", attrs->cap.max_recv_wr);
	QL_DPRINT12(ha, "attrs->cap.max_send_sge = 0x%x\n", attrs->cap.max_send_sge);
	QL_DPRINT12(ha, "attrs->cap.max_recv_sge = 0x%x\n", attrs->cap.max_recv_sge);
	QL_DPRINT12(ha, "attrs->cap.max_inline_data = 0x%x\n",
		attrs->cap.max_inline_data);

#if __FreeBSD_version < 1102000
	QL_DPRINT12(ha, "attrs->cap.qpg_tss_mask_sz = 0x%x\n",
		attrs->cap.qpg_tss_mask_sz);
#endif

	QL_DPRINT12(ha, "\n\nqattr->vendor_id = 0x%x\n", qattr->vendor_id);
	QL_DPRINT12(ha, "qattr->vendor_part_id = 0x%x\n", qattr->vendor_part_id);
	QL_DPRINT12(ha, "qattr->hw_ver = 0x%x\n", qattr->hw_ver);
	QL_DPRINT12(ha, "qattr->fw_ver = %p\n", (void *)qattr->fw_ver);
	QL_DPRINT12(ha, "qattr->node_guid = %p\n", (void *)qattr->node_guid);
	QL_DPRINT12(ha, "qattr->sys_image_guid = %p\n",
		(void *)qattr->sys_image_guid);
	QL_DPRINT12(ha, "qattr->max_cnq = 0x%x\n", qattr->max_cnq);
	QL_DPRINT12(ha, "qattr->max_sge = 0x%x\n", qattr->max_sge);
	QL_DPRINT12(ha, "qattr->max_srq_sge = 0x%x\n", qattr->max_srq_sge);
	QL_DPRINT12(ha, "qattr->max_inline = 0x%x\n", qattr->max_inline);
	QL_DPRINT12(ha, "qattr->max_wqe = 0x%x\n", qattr->max_wqe);
	QL_DPRINT12(ha, "qattr->max_srq_wqe = 0x%x\n", qattr->max_srq_wqe);
	QL_DPRINT12(ha, "qattr->max_qp_resp_rd_atomic_resc = 0x%x\n",
		qattr->max_qp_resp_rd_atomic_resc);
	QL_DPRINT12(ha, "qattr->max_qp_req_rd_atomic_resc = 0x%x\n",
		qattr->max_qp_req_rd_atomic_resc);
	QL_DPRINT12(ha, "qattr->max_dev_resp_rd_atomic_resc = 0x%x\n",
		qattr->max_dev_resp_rd_atomic_resc);
	QL_DPRINT12(ha, "qattr->max_cq = 0x%x\n", qattr->max_cq);
	QL_DPRINT12(ha, "qattr->max_qp = 0x%x\n", qattr->max_qp);
	QL_DPRINT12(ha, "qattr->max_srq = 0x%x\n", qattr->max_srq);
	QL_DPRINT12(ha, "qattr->max_mr = 0x%x\n", qattr->max_mr);
	QL_DPRINT12(ha, "qattr->max_mr_size = %p\n", (void *)qattr->max_mr_size);
	QL_DPRINT12(ha, "qattr->max_cqe = 0x%x\n", qattr->max_cqe);
	QL_DPRINT12(ha, "qattr->max_mw = 0x%x\n", qattr->max_mw);
	QL_DPRINT12(ha, "qattr->max_fmr = 0x%x\n", qattr->max_fmr);
	QL_DPRINT12(ha, "qattr->max_mr_mw_fmr_pbl = 0x%x\n",
		qattr->max_mr_mw_fmr_pbl);
	QL_DPRINT12(ha, "qattr->max_mr_mw_fmr_size = %p\n",
		(void *)qattr->max_mr_mw_fmr_size);
	QL_DPRINT12(ha, "qattr->max_pd = 0x%x\n", qattr->max_pd);
	QL_DPRINT12(ha, "qattr->max_ah = 0x%x\n", qattr->max_ah);
	QL_DPRINT12(ha, "qattr->max_pkey = 0x%x\n", qattr->max_pkey);
	QL_DPRINT12(ha, "qattr->max_srq_wr = 0x%x\n", qattr->max_srq_wr);
	QL_DPRINT12(ha, "qattr->max_stats_queues = 0x%x\n",
		qattr->max_stats_queues);
	//QL_DPRINT12(ha, "qattr->dev_caps = 0x%x\n", qattr->dev_caps);
	QL_DPRINT12(ha, "qattr->page_size_caps = %p\n",
		(void *)qattr->page_size_caps);
	QL_DPRINT12(ha, "qattr->dev_ack_delay = 0x%x\n", qattr->dev_ack_delay);
	QL_DPRINT12(ha, "qattr->reserved_lkey = 0x%x\n", qattr->reserved_lkey);
	QL_DPRINT12(ha, "qattr->bad_pkey_counter = 0x%x\n",
		qattr->bad_pkey_counter);

	if ((attrs->qp_type == IB_QPT_GSI) && udata) {
		QL_DPRINT12(ha, "unexpected udata when creating GSI QP\n");
		return -EINVAL;
	}

	if (udata && !(ibpd->uobject && ibpd->uobject->context)) {
		QL_DPRINT12(ha, "called from user without context\n");
		return -EINVAL;
	}

	/* QP0... attrs->qp_type == IB_QPT_GSI */
	if (attrs->qp_type != IB_QPT_RC && attrs->qp_type != IB_QPT_GSI) {
		QL_DPRINT12(ha, "unsupported qp type=0x%x requested\n", 
			   attrs->qp_type);
		return -EINVAL;
	}
	if (attrs->qp_type == IB_QPT_GSI && attrs->srq) {
		QL_DPRINT12(ha, "cannot create GSI qp with SRQ\n");
		return -EINVAL;
	}
	/* Skip the check for QP1 to support CM size of 128 */
	if (attrs->cap.max_send_wr > qattr->max_wqe) {
		QL_DPRINT12(ha, "cannot create a SQ with %d elements "
			" (max_send_wr=0x%x)\n",
			attrs->cap.max_send_wr, qattr->max_wqe);
		return -EINVAL;
	}
	if (!attrs->srq && (attrs->cap.max_recv_wr > qattr->max_wqe)) {
		QL_DPRINT12(ha, "cannot create a RQ with %d elements"
			" (max_recv_wr=0x%x)\n",
			attrs->cap.max_recv_wr, qattr->max_wqe);
		return -EINVAL;
	}
	if (attrs->cap.max_inline_data > qattr->max_inline) {
		QL_DPRINT12(ha,
			"unsupported inline data size=0x%x "
			"requested (max_inline=0x%x)\n",
			attrs->cap.max_inline_data, qattr->max_inline);
		return -EINVAL;
	}
	if (attrs->cap.max_send_sge > qattr->max_sge) {
		QL_DPRINT12(ha,
			"unsupported send_sge=0x%x "
			"requested (max_send_sge=0x%x)\n",
			attrs->cap.max_send_sge, qattr->max_sge);
		return -EINVAL;
	}
	if (attrs->cap.max_recv_sge > qattr->max_sge) {
		QL_DPRINT12(ha,
			"unsupported recv_sge=0x%x requested "
			" (max_recv_sge=0x%x)\n",
			attrs->cap.max_recv_sge, qattr->max_sge);
		return -EINVAL;
	}
	/* unprivileged user space cannot create special QP */
	if (ibpd->uobject && attrs->qp_type == IB_QPT_GSI) {
		QL_DPRINT12(ha,
			"userspace can't create special QPs of type=0x%x\n",
			attrs->qp_type);
		return -EINVAL;
	}
	/* allow creating only one GSI type of QP */
	if (attrs->qp_type == IB_QPT_GSI && dev->gsi_qp_created) {
		QL_DPRINT12(ha,
			"create qp: GSI special QPs already created.\n");
		return -EINVAL;
	}

	/* verify consumer QPs are not trying to use GSI QP's CQ */
	if ((attrs->qp_type != IB_QPT_GSI) && (dev->gsi_qp_created)) {
		struct qlnxr_cq *send_cq = get_qlnxr_cq(attrs->send_cq);
		struct qlnxr_cq *recv_cq = get_qlnxr_cq(attrs->recv_cq);

		if ((send_cq->cq_type == QLNXR_CQ_TYPE_GSI) ||
		    (recv_cq->cq_type == QLNXR_CQ_TYPE_GSI)) {
			QL_DPRINT11(ha, "consumer QP cannot use GSI CQs.\n");
			return -EINVAL;
		}
	}
	QL_DPRINT12(ha, "exit\n");
	return 0;
}