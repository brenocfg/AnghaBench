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
struct mlx5_wq {int /*<<< orphan*/ * wr_data; } ;
struct mlx5_cqe64 {int /*<<< orphan*/  byte_cnt; int /*<<< orphan*/  sop_drop_qpn; } ;
struct ibv_wc {int byte_len; int /*<<< orphan*/  opcode; int /*<<< orphan*/  wc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_WC_COMP_SWAP ; 
 int /*<<< orphan*/  IBV_WC_FETCH_ADD ; 
 int /*<<< orphan*/  IBV_WC_RDMA_READ ; 
 int /*<<< orphan*/  IBV_WC_RDMA_WRITE ; 
 int /*<<< orphan*/  IBV_WC_SEND ; 
 int /*<<< orphan*/  IBV_WC_TSO ; 
 int /*<<< orphan*/  IBV_WC_WITH_IMM ; 
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
 int /*<<< orphan*/  SWITCH_FALLTHROUGH ; 
 int be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void handle_good_req(struct ibv_wc *wc, struct mlx5_cqe64 *cqe, struct mlx5_wq *wq, int idx)
{
	switch (be32toh(cqe->sop_drop_qpn) >> 24) {
	case MLX5_OPCODE_RDMA_WRITE_IMM:
		wc->wc_flags |= IBV_WC_WITH_IMM;
		SWITCH_FALLTHROUGH;
	case MLX5_OPCODE_RDMA_WRITE:
		wc->opcode    = IBV_WC_RDMA_WRITE;
		break;
	case MLX5_OPCODE_SEND_IMM:
		wc->wc_flags |= IBV_WC_WITH_IMM;
		SWITCH_FALLTHROUGH;
	case MLX5_OPCODE_SEND:
	case MLX5_OPCODE_SEND_INVAL:
		wc->opcode    = IBV_WC_SEND;
		break;
	case MLX5_OPCODE_RDMA_READ:
		wc->opcode    = IBV_WC_RDMA_READ;
		wc->byte_len  = be32toh(cqe->byte_cnt);
		break;
	case MLX5_OPCODE_ATOMIC_CS:
		wc->opcode    = IBV_WC_COMP_SWAP;
		wc->byte_len  = 8;
		break;
	case MLX5_OPCODE_ATOMIC_FA:
		wc->opcode    = IBV_WC_FETCH_ADD;
		wc->byte_len  = 8;
		break;
	case MLX5_OPCODE_UMR:
		wc->opcode = wq->wr_data[idx];
		break;
	case MLX5_OPCODE_TSO:
		wc->opcode    = IBV_WC_TSO;
		break;
	}
}