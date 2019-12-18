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
struct mlx5_cq {int umr_opcode; TYPE_1__* cqe64; } ;
struct mlx5_context {int /*<<< orphan*/  dbg_fp; } ;
struct ibv_cq_ex {int /*<<< orphan*/  context; } ;
typedef  enum ibv_wc_opcode { ____Placeholder_ibv_wc_opcode } ibv_wc_opcode ;
struct TYPE_2__ {int /*<<< orphan*/  sop_drop_qpn; } ;

/* Variables and functions */
 int IBV_WC_COMP_SWAP ; 
 int IBV_WC_FETCH_ADD ; 
 int IBV_WC_RDMA_READ ; 
 int IBV_WC_RDMA_WRITE ; 
 int IBV_WC_RECV ; 
 int IBV_WC_RECV_RDMA_WITH_IMM ; 
 int IBV_WC_SEND ; 
 int IBV_WC_TSO ; 
#define  MLX5_CQE_REQ 142 
#define  MLX5_CQE_RESP_SEND 141 
#define  MLX5_CQE_RESP_SEND_IMM 140 
#define  MLX5_CQE_RESP_SEND_INV 139 
#define  MLX5_CQE_RESP_WR_IMM 138 
 int /*<<< orphan*/  MLX5_DBG_CQ_CQE ; 
#define  MLX5_OPCODE_ATOMIC_CS 137 
#define  MLX5_OPCODE_ATOMIC_FA 136 
#define  MLX5_OPCODE_RDMA_READ 135 
#define  MLX5_OPCODE_RDMA_WRITE 134 
#define  MLX5_OPCODE_RDMA_WRITE_IMM 133 
#define  MLX5_OPCODE_SEND 132 
#define  MLX5_OPCODE_SEND_IMM 131 
#define  MLX5_OPCODE_SEND_INVAL 130 
#define  MLX5_OPCODE_TSO 129 
#define  MLX5_OPCODE_UMR 128 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlx5dv_get_cqe_opcode (TYPE_1__*) ; 
 struct mlx5_cq* to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx5_context* to_mctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum ibv_wc_opcode mlx5_cq_read_wc_opcode(struct ibv_cq_ex *ibcq)
{
	struct mlx5_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));

	switch (mlx5dv_get_cqe_opcode(cq->cqe64)) {
	case MLX5_CQE_RESP_WR_IMM:
		return IBV_WC_RECV_RDMA_WITH_IMM;
	case MLX5_CQE_RESP_SEND:
	case MLX5_CQE_RESP_SEND_IMM:
	case MLX5_CQE_RESP_SEND_INV:
		return IBV_WC_RECV;
	case MLX5_CQE_REQ:
		switch (be32toh(cq->cqe64->sop_drop_qpn) >> 24) {
		case MLX5_OPCODE_RDMA_WRITE_IMM:
		case MLX5_OPCODE_RDMA_WRITE:
			return IBV_WC_RDMA_WRITE;
		case MLX5_OPCODE_SEND_IMM:
		case MLX5_OPCODE_SEND:
		case MLX5_OPCODE_SEND_INVAL:
			return IBV_WC_SEND;
		case MLX5_OPCODE_RDMA_READ:
			return IBV_WC_RDMA_READ;
		case MLX5_OPCODE_ATOMIC_CS:
			return IBV_WC_COMP_SWAP;
		case MLX5_OPCODE_ATOMIC_FA:
			return IBV_WC_FETCH_ADD;
		case MLX5_OPCODE_UMR:
			return cq->umr_opcode;
		case MLX5_OPCODE_TSO:
			return IBV_WC_TSO;
		}
	}

#ifdef MLX5_DEBUG
{
	struct mlx5_context *ctx = to_mctx(ibcq->context);

	mlx5_dbg(ctx->dbg_fp, MLX5_DBG_CQ_CQE, "un-expected opcode in cqe\n");
}
#endif
	return 0;
}