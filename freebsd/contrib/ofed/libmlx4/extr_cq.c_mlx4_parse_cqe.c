#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct mlx4_wq {int tail; int wqe_cnt; int /*<<< orphan*/ * wrid; } ;
struct mlx4_srq {int /*<<< orphan*/ * wrid; } ;
struct TYPE_4__ {int qp_num; scalar_t__ srq; } ;
struct TYPE_5__ {TYPE_1__ qp; } ;
struct mlx4_qp {int qp_cap_cache; scalar_t__ link_layer; struct mlx4_wq rq; struct mlx4_wq sq; TYPE_2__ verbs_qp; } ;
struct mlx4_err_cqe {int /*<<< orphan*/  vendor_err; } ;
struct mlx4_cqe {int vlan_my_qpn; int owner_sr_opcode; int g_mlpath_rqpn; int byte_cnt; int immed_rss_invalid; int status; int /*<<< orphan*/  sl_vid; int /*<<< orphan*/  rlid; int /*<<< orphan*/  wqe_index; } ;
struct TYPE_6__ {int status; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  context; } ;
struct mlx4_cq {int /*<<< orphan*/  flags; TYPE_3__ ibv_cq; struct mlx4_cqe* cqe; } ;
struct mlx4_context {int /*<<< orphan*/  xsrq_table; } ;
struct ibv_wc {int qp_num; int status; int byte_len; int wc_flags; int imm_data; int slid; int src_qp; int dlid_path_bits; int pkey_index; int sl; void* opcode; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  wr_id; } ;
typedef  enum ibv_wc_status { ____Placeholder_ibv_wc_status } ibv_wc_status ;

/* Variables and functions */
 int CQ_OK ; 
 int CQ_POLL_ERR ; 
 scalar_t__ IBV_LINK_LAYER_ETHERNET ; 
 int IBV_WC_GRH ; 
 int IBV_WC_IP_CSUM_OK_SHIFT ; 
 void* IBV_WC_RECV ; 
 void* IBV_WC_RECV_RDMA_WITH_IMM ; 
 int IBV_WC_SUCCESS ; 
 void* IBV_WC_WITH_IMM ; 
 int IBV_WC_WITH_INV ; 
 int MLX4_CQE_IS_SEND_MASK ; 
 int MLX4_CQE_OPCODE_ERROR ; 
 int MLX4_CQE_OPCODE_MASK ; 
 int MLX4_CQE_QPN_MASK ; 
 int /*<<< orphan*/  MLX4_CQE_STATUS_IPV4_CSUM_OK ; 
 int /*<<< orphan*/  MLX4_CQ_FLAGS_RX_CSUM_VALID ; 
#define  MLX4_RECV_OPCODE_RDMA_WRITE_IMM 131 
#define  MLX4_RECV_OPCODE_SEND 130 
#define  MLX4_RECV_OPCODE_SEND_IMM 129 
#define  MLX4_RECV_OPCODE_SEND_INVAL 128 
 int MLX4_RX_CSUM_VALID ; 
 int MLX4_XRC_QPN_BIT ; 
 int be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int) ; 
 int /*<<< orphan*/  handle_good_req (struct ibv_wc*,struct mlx4_cqe*) ; 
 int htobe32 (int /*<<< orphan*/ ) ; 
 struct mlx4_qp* mlx4_find_qp (struct mlx4_context*,int) ; 
 struct mlx4_srq* mlx4_find_xsrq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx4_free_srq_wqe (struct mlx4_srq*,size_t) ; 
 int mlx4_handle_error_cqe (struct mlx4_err_cqe*) ; 
 struct mlx4_context* to_mctx (int /*<<< orphan*/ ) ; 
 struct mlx4_srq* to_msrq (scalar_t__) ; 

__attribute__((used)) static inline int mlx4_parse_cqe(struct mlx4_cq *cq,
					struct mlx4_cqe *cqe,
					struct mlx4_qp **cur_qp,
					struct ibv_wc *wc, int lazy)
{
	struct mlx4_wq *wq;
	struct mlx4_srq *srq;
	uint32_t qpn;
	uint32_t g_mlpath_rqpn;
	uint64_t *pwr_id;
	uint16_t wqe_index;
	struct mlx4_err_cqe *ecqe;
	struct mlx4_context *mctx;
	int is_error;
	int is_send;
	enum ibv_wc_status *pstatus;

	mctx = to_mctx(cq->ibv_cq.context);
	qpn = be32toh(cqe->vlan_my_qpn) & MLX4_CQE_QPN_MASK;
	if (lazy) {
		cq->cqe = cqe;
		cq->flags &= (~MLX4_CQ_FLAGS_RX_CSUM_VALID);
	} else
		wc->qp_num = qpn;

	is_send  = cqe->owner_sr_opcode & MLX4_CQE_IS_SEND_MASK;
	is_error = (cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) ==
		MLX4_CQE_OPCODE_ERROR;

	if ((qpn & MLX4_XRC_QPN_BIT) && !is_send) {
		/*
		 * We do not have to take the XSRQ table lock here,
		 * because CQs will be locked while SRQs are removed
		 * from the table.
		 */
		srq = mlx4_find_xsrq(&mctx->xsrq_table,
				     be32toh(cqe->g_mlpath_rqpn) & MLX4_CQE_QPN_MASK);
		if (!srq)
			return CQ_POLL_ERR;
	} else {
		if (!*cur_qp || (qpn != (*cur_qp)->verbs_qp.qp.qp_num)) {
			/*
			 * We do not have to take the QP table lock here,
			 * because CQs will be locked while QPs are removed
			 * from the table.
			 */
			*cur_qp = mlx4_find_qp(mctx, qpn);
			if (!*cur_qp)
				return CQ_POLL_ERR;
		}
		srq = ((*cur_qp)->verbs_qp.qp.srq) ? to_msrq((*cur_qp)->verbs_qp.qp.srq) : NULL;
	}

	pwr_id = lazy ? &cq->ibv_cq.wr_id : &wc->wr_id;
	if (is_send) {
		wq = &(*cur_qp)->sq;
		wqe_index = be16toh(cqe->wqe_index);
		wq->tail += (uint16_t) (wqe_index - (uint16_t) wq->tail);
		*pwr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		++wq->tail;
	} else if (srq) {
		wqe_index = be16toh(cqe->wqe_index);
		*pwr_id = srq->wrid[wqe_index];
		mlx4_free_srq_wqe(srq, wqe_index);
	} else {
		wq = &(*cur_qp)->rq;
		*pwr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		++wq->tail;
	}

	pstatus = lazy ? &cq->ibv_cq.status : &wc->status;
	if (is_error) {
		ecqe = (struct mlx4_err_cqe *)cqe;
		*pstatus = mlx4_handle_error_cqe(ecqe);
		if (!lazy)
			wc->vendor_err = ecqe->vendor_err;
		return CQ_OK;
	}

	*pstatus = IBV_WC_SUCCESS;
	if (lazy) {
		if (!is_send)
			if ((*cur_qp) && ((*cur_qp)->qp_cap_cache & MLX4_RX_CSUM_VALID))
				cq->flags |= MLX4_CQ_FLAGS_RX_CSUM_VALID;
	} else if (is_send) {
		handle_good_req(wc, cqe);
	} else {
		wc->byte_len = be32toh(cqe->byte_cnt);

		switch (cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) {
		case MLX4_RECV_OPCODE_RDMA_WRITE_IMM:
			wc->opcode   = IBV_WC_RECV_RDMA_WITH_IMM;
			wc->wc_flags = IBV_WC_WITH_IMM;
			wc->imm_data = cqe->immed_rss_invalid;
			break;
		case MLX4_RECV_OPCODE_SEND_INVAL:
			wc->opcode   = IBV_WC_RECV;
			wc->wc_flags |= IBV_WC_WITH_INV;
			wc->imm_data = be32toh(cqe->immed_rss_invalid);
			break;
		case MLX4_RECV_OPCODE_SEND:
			wc->opcode   = IBV_WC_RECV;
			wc->wc_flags = 0;
			break;
		case MLX4_RECV_OPCODE_SEND_IMM:
			wc->opcode   = IBV_WC_RECV;
			wc->wc_flags = IBV_WC_WITH_IMM;
			wc->imm_data = cqe->immed_rss_invalid;
			break;
		}

		wc->slid	   = be16toh(cqe->rlid);
		g_mlpath_rqpn	   = be32toh(cqe->g_mlpath_rqpn);
		wc->src_qp	   = g_mlpath_rqpn & 0xffffff;
		wc->dlid_path_bits = (g_mlpath_rqpn >> 24) & 0x7f;
		wc->wc_flags	  |= g_mlpath_rqpn & 0x80000000 ? IBV_WC_GRH : 0;
		wc->pkey_index     = be32toh(cqe->immed_rss_invalid) & 0x7f;
		/* When working with xrc srqs, don't have qp to check link layer.
		* Using IB SL, should consider Roce. (TBD)
		*/
		if ((*cur_qp) && (*cur_qp)->link_layer == IBV_LINK_LAYER_ETHERNET)
			wc->sl	   = be16toh(cqe->sl_vid) >> 13;
		else
			wc->sl	   = be16toh(cqe->sl_vid) >> 12;

		if ((*cur_qp) && ((*cur_qp)->qp_cap_cache & MLX4_RX_CSUM_VALID)) {
			wc->wc_flags |= ((cqe->status & htobe32(MLX4_CQE_STATUS_IPV4_CSUM_OK)) ==
				 htobe32(MLX4_CQE_STATUS_IPV4_CSUM_OK)) <<
				IBV_WC_IP_CSUM_OK_SHIFT;
		}
	}

	return CQ_OK;
}