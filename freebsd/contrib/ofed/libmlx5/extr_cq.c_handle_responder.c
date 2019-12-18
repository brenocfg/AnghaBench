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
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct mlx5_wq {int tail; int wqe_cnt; int /*<<< orphan*/ * wrid; } ;
struct mlx5_srq {int /*<<< orphan*/ * wrid; } ;
struct mlx5_resource {scalar_t__ type; } ;
struct mlx5_qp {int qp_cap_cache; struct mlx5_wq rq; } ;
struct mlx5_cqe64 {int byte_cnt; int op_own; int hds_ip_ext; int imm_inval_pkey; int flags_rqpn; int ml_path; int /*<<< orphan*/  slid; int /*<<< orphan*/  wqe_counter; } ;
struct ibv_wc {int byte_len; int wc_flags; int imm_data; int sl; int src_qp; int dlid_path_bits; int pkey_index; void* slid; void* opcode; int /*<<< orphan*/  wr_id; } ;
struct TYPE_2__ {struct mlx5_wq rq; } ;

/* Variables and functions */
 int IBV_WC_GRH ; 
 int IBV_WC_IP_CSUM_OK_SHIFT ; 
 void* IBV_WC_RECV ; 
 void* IBV_WC_RECV_RDMA_WITH_IMM ; 
 int IBV_WC_SUCCESS ; 
 int IBV_WC_WITH_IMM ; 
 int IBV_WC_WITH_INV ; 
 scalar_t__ MLX5_CQE_L3_HDR_TYPE_IPV4 ; 
 int MLX5_CQE_L3_OK ; 
 int MLX5_CQE_L4_OK ; 
#define  MLX5_CQE_RESP_SEND 131 
#define  MLX5_CQE_RESP_SEND_IMM 130 
#define  MLX5_CQE_RESP_SEND_INV 129 
#define  MLX5_CQE_RESP_WR_IMM 128 
 int MLX5_INLINE_SCATTER_32 ; 
 int MLX5_INLINE_SCATTER_64 ; 
 scalar_t__ MLX5_RSC_TYPE_QP ; 
 int MLX5_RX_CSUM_VALID ; 
 void* be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int) ; 
 scalar_t__ get_cqe_l3_hdr_type (struct mlx5_cqe64*) ; 
 scalar_t__ likely (int) ; 
 int mlx5_copy_to_recv_srq (struct mlx5_srq*,size_t,struct mlx5_cqe64*,int) ; 
 int mlx5_copy_to_recv_wqe (struct mlx5_qp*,size_t,struct mlx5_cqe64*,int) ; 
 int /*<<< orphan*/  mlx5_free_srq_wqe (struct mlx5_srq*,size_t) ; 
 struct mlx5_qp* rsc_to_mqp (struct mlx5_resource*) ; 
 TYPE_1__* rsc_to_mrwq (struct mlx5_resource*) ; 

__attribute__((used)) static inline int handle_responder(struct ibv_wc *wc, struct mlx5_cqe64 *cqe,
				   struct mlx5_resource *cur_rsc, struct mlx5_srq *srq)
{
	uint16_t	wqe_ctr;
	struct mlx5_wq *wq;
	struct mlx5_qp *qp = rsc_to_mqp(cur_rsc);
	uint8_t g;
	int err = 0;

	wc->byte_len = be32toh(cqe->byte_cnt);
	if (srq) {
		wqe_ctr = be16toh(cqe->wqe_counter);
		wc->wr_id = srq->wrid[wqe_ctr];
		mlx5_free_srq_wqe(srq, wqe_ctr);
		if (cqe->op_own & MLX5_INLINE_SCATTER_32)
			err = mlx5_copy_to_recv_srq(srq, wqe_ctr, cqe,
						    wc->byte_len);
		else if (cqe->op_own & MLX5_INLINE_SCATTER_64)
			err = mlx5_copy_to_recv_srq(srq, wqe_ctr, cqe - 1,
						    wc->byte_len);
	} else {
		if (likely(cur_rsc->type == MLX5_RSC_TYPE_QP)) {
			wq = &qp->rq;
			if (qp->qp_cap_cache & MLX5_RX_CSUM_VALID)
				wc->wc_flags |= (!!(cqe->hds_ip_ext & MLX5_CQE_L4_OK) &
						 !!(cqe->hds_ip_ext & MLX5_CQE_L3_OK) &
						(get_cqe_l3_hdr_type(cqe) ==
						MLX5_CQE_L3_HDR_TYPE_IPV4)) <<
						IBV_WC_IP_CSUM_OK_SHIFT;
		} else {
			wq = &(rsc_to_mrwq(cur_rsc)->rq);
		}

		wqe_ctr = wq->tail & (wq->wqe_cnt - 1);
		wc->wr_id = wq->wrid[wqe_ctr];
		++wq->tail;
		if (cqe->op_own & MLX5_INLINE_SCATTER_32)
			err = mlx5_copy_to_recv_wqe(qp, wqe_ctr, cqe,
						    wc->byte_len);
		else if (cqe->op_own & MLX5_INLINE_SCATTER_64)
			err = mlx5_copy_to_recv_wqe(qp, wqe_ctr, cqe - 1,
						    wc->byte_len);
	}
	if (err)
		return err;

	switch (cqe->op_own >> 4) {
	case MLX5_CQE_RESP_WR_IMM:
		wc->opcode	= IBV_WC_RECV_RDMA_WITH_IMM;
		wc->wc_flags	|= IBV_WC_WITH_IMM;
		wc->imm_data = cqe->imm_inval_pkey;
		break;
	case MLX5_CQE_RESP_SEND:
		wc->opcode   = IBV_WC_RECV;
		break;
	case MLX5_CQE_RESP_SEND_IMM:
		wc->opcode	= IBV_WC_RECV;
		wc->wc_flags	|= IBV_WC_WITH_IMM;
		wc->imm_data = cqe->imm_inval_pkey;
		break;
	case MLX5_CQE_RESP_SEND_INV:
		wc->opcode = IBV_WC_RECV;
		wc->wc_flags |= IBV_WC_WITH_INV;
		wc->imm_data = be32toh(cqe->imm_inval_pkey);
		break;
	}
	wc->slid	   = be16toh(cqe->slid);
	wc->sl		   = (be32toh(cqe->flags_rqpn) >> 24) & 0xf;
	wc->src_qp	   = be32toh(cqe->flags_rqpn) & 0xffffff;
	wc->dlid_path_bits = cqe->ml_path & 0x7f;
	g = (be32toh(cqe->flags_rqpn) >> 28) & 3;
	wc->wc_flags |= g ? IBV_WC_GRH : 0;
	wc->pkey_index     = be32toh(cqe->imm_inval_pkey) & 0xffff;

	return IBV_WC_SUCCESS;
}