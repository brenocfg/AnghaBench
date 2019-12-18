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
struct op {int /*<<< orphan*/  end_poll; int /*<<< orphan*/  next_poll; int /*<<< orphan*/  start_poll; } ;
struct TYPE_4__ {int /*<<< orphan*/  read_flow_tag; int /*<<< orphan*/  read_cvlan; int /*<<< orphan*/  read_completion_ts; int /*<<< orphan*/  read_dlid_path_bits; int /*<<< orphan*/  read_sl; int /*<<< orphan*/  read_slid; int /*<<< orphan*/  read_src_qp; int /*<<< orphan*/  read_qp_num; int /*<<< orphan*/  read_imm_data; int /*<<< orphan*/  read_byte_len; int /*<<< orphan*/  read_wc_flags; int /*<<< orphan*/  read_vendor_err; int /*<<< orphan*/  read_opcode; int /*<<< orphan*/  end_poll; int /*<<< orphan*/  next_poll; int /*<<< orphan*/  start_poll; } ;
struct mlx5_cq {int flags; TYPE_2__ ibv_cq; scalar_t__ stall_enable; scalar_t__ stall_adaptive_enable; } ;
struct mlx5_context {scalar_t__ cqe_version; } ;
struct ibv_cq_init_attr_ex {int wc_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 size_t ADAPTIVE ; 
 int IBV_WC_EX_WITH_BYTE_LEN ; 
 int IBV_WC_EX_WITH_COMPLETION_TIMESTAMP ; 
 int IBV_WC_EX_WITH_CVLAN ; 
 int IBV_WC_EX_WITH_DLID_PATH_BITS ; 
 int IBV_WC_EX_WITH_FLOW_TAG ; 
 int IBV_WC_EX_WITH_IMM ; 
 int IBV_WC_EX_WITH_QP_NUM ; 
 int IBV_WC_EX_WITH_SL ; 
 int IBV_WC_EX_WITH_SLID ; 
 int IBV_WC_EX_WITH_SRC_QP ; 
 int MLX5_CQ_FLAGS_SINGLE_THREADED ; 
 size_t SINGLE_THREADED ; 
 size_t STALL ; 
 size_t V1 ; 
 TYPE_1__* ibv_cq_ex_to_cq (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_cq_read_flow_tag ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_byte_len ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_completion_ts ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_cvlan ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_dlid_path_bits ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_flags ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_imm_data ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_opcode ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_qp_num ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_sl ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_slid ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_src_qp ; 
 int /*<<< orphan*/  mlx5_cq_read_wc_vendor_err ; 
 struct op* ops ; 
 struct mlx5_context* to_mctx (int /*<<< orphan*/ ) ; 

void mlx5_cq_fill_pfns(struct mlx5_cq *cq, const struct ibv_cq_init_attr_ex *cq_attr)
{
	struct mlx5_context *mctx = to_mctx(ibv_cq_ex_to_cq(&cq->ibv_cq)->context);
	const struct op *poll_ops = &ops[((cq->stall_enable && cq->stall_adaptive_enable) ? ADAPTIVE : 0) |
					 (mctx->cqe_version ? V1 : 0) |
					 (cq->flags & MLX5_CQ_FLAGS_SINGLE_THREADED ?
						      SINGLE_THREADED : 0) |
					 (cq->stall_enable ? STALL : 0)];

	cq->ibv_cq.start_poll = poll_ops->start_poll;
	cq->ibv_cq.next_poll = poll_ops->next_poll;
	cq->ibv_cq.end_poll = poll_ops->end_poll;

	cq->ibv_cq.read_opcode = mlx5_cq_read_wc_opcode;
	cq->ibv_cq.read_vendor_err = mlx5_cq_read_wc_vendor_err;
	cq->ibv_cq.read_wc_flags = mlx5_cq_read_wc_flags;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_BYTE_LEN)
		cq->ibv_cq.read_byte_len = mlx5_cq_read_wc_byte_len;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_IMM)
		cq->ibv_cq.read_imm_data = mlx5_cq_read_wc_imm_data;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_QP_NUM)
		cq->ibv_cq.read_qp_num = mlx5_cq_read_wc_qp_num;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_SRC_QP)
		cq->ibv_cq.read_src_qp = mlx5_cq_read_wc_src_qp;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_SLID)
		cq->ibv_cq.read_slid = mlx5_cq_read_wc_slid;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_SL)
		cq->ibv_cq.read_sl = mlx5_cq_read_wc_sl;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_DLID_PATH_BITS)
		cq->ibv_cq.read_dlid_path_bits = mlx5_cq_read_wc_dlid_path_bits;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_COMPLETION_TIMESTAMP)
		cq->ibv_cq.read_completion_ts = mlx5_cq_read_wc_completion_ts;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_CVLAN)
		cq->ibv_cq.read_cvlan = mlx5_cq_read_wc_cvlan;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_FLOW_TAG)
		cq->ibv_cq.read_flow_tag = mlx5_cq_read_flow_tag;
}