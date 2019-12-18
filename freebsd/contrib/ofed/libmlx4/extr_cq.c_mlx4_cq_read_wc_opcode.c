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
struct mlx4_cq {TYPE_1__* cqe; } ;
struct ibv_cq_ex {int dummy; } ;
typedef  enum ibv_wc_opcode { ____Placeholder_ibv_wc_opcode } ibv_wc_opcode ;
struct TYPE_2__ {int owner_sr_opcode; } ;

/* Variables and functions */
 int IBV_WC_BIND_MW ; 
 int IBV_WC_COMP_SWAP ; 
 int IBV_WC_FETCH_ADD ; 
 int IBV_WC_LOCAL_INV ; 
 int IBV_WC_RDMA_READ ; 
 int IBV_WC_RDMA_WRITE ; 
 int IBV_WC_RECV ; 
 int IBV_WC_RECV_RDMA_WITH_IMM ; 
 int IBV_WC_SEND ; 
 int MLX4_CQE_IS_SEND_MASK ; 
 int MLX4_CQE_OPCODE_MASK ; 
#define  MLX4_OPCODE_ATOMIC_CS 141 
#define  MLX4_OPCODE_ATOMIC_FA 140 
#define  MLX4_OPCODE_BIND_MW 139 
#define  MLX4_OPCODE_LOCAL_INVAL 138 
#define  MLX4_OPCODE_RDMA_READ 137 
#define  MLX4_OPCODE_RDMA_WRITE 136 
#define  MLX4_OPCODE_RDMA_WRITE_IMM 135 
#define  MLX4_OPCODE_SEND 134 
#define  MLX4_OPCODE_SEND_IMM 133 
#define  MLX4_OPCODE_SEND_INVAL 132 
#define  MLX4_RECV_OPCODE_RDMA_WRITE_IMM 131 
#define  MLX4_RECV_OPCODE_SEND 130 
#define  MLX4_RECV_OPCODE_SEND_IMM 129 
#define  MLX4_RECV_OPCODE_SEND_INVAL 128 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 struct mlx4_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ibv_wc_opcode mlx4_cq_read_wc_opcode(struct ibv_cq_ex *ibcq)
{
	struct mlx4_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));

	if (cq->cqe->owner_sr_opcode & MLX4_CQE_IS_SEND_MASK) {
		switch (cq->cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) {
		case MLX4_OPCODE_RDMA_WRITE_IMM:
		case MLX4_OPCODE_RDMA_WRITE:
			return IBV_WC_RDMA_WRITE;
		case MLX4_OPCODE_SEND_INVAL:
		case MLX4_OPCODE_SEND_IMM:
		case MLX4_OPCODE_SEND:
			return IBV_WC_SEND;
		case MLX4_OPCODE_RDMA_READ:
			return IBV_WC_RDMA_READ;
		case MLX4_OPCODE_ATOMIC_CS:
			return IBV_WC_COMP_SWAP;
		case MLX4_OPCODE_ATOMIC_FA:
			return IBV_WC_FETCH_ADD;
		case MLX4_OPCODE_LOCAL_INVAL:
			return IBV_WC_LOCAL_INV;
		case MLX4_OPCODE_BIND_MW:
			return IBV_WC_BIND_MW;
		}
	} else {
		switch (cq->cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) {
		case MLX4_RECV_OPCODE_RDMA_WRITE_IMM:
			return IBV_WC_RECV_RDMA_WITH_IMM;
		case MLX4_RECV_OPCODE_SEND_INVAL:
		case MLX4_RECV_OPCODE_SEND_IMM:
		case MLX4_RECV_OPCODE_SEND:
			return IBV_WC_RECV;
		}
	}

	return 0;
}