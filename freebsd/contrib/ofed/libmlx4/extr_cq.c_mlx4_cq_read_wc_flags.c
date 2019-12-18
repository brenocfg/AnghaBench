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
struct mlx4_cq {int flags; TYPE_1__* cqe; } ;
struct ibv_cq_ex {int dummy; } ;
struct TYPE_2__ {int owner_sr_opcode; int status; int /*<<< orphan*/  g_mlpath_rqpn; } ;

/* Variables and functions */
 int IBV_WC_GRH ; 
 int IBV_WC_IP_CSUM_OK_SHIFT ; 
 int IBV_WC_WITH_IMM ; 
 int IBV_WC_WITH_INV ; 
 int MLX4_CQE_IS_SEND_MASK ; 
 int MLX4_CQE_OPCODE_MASK ; 
 int /*<<< orphan*/  MLX4_CQE_STATUS_IPV4_CSUM_OK ; 
 int MLX4_CQ_FLAGS_RX_CSUM_VALID ; 
#define  MLX4_OPCODE_RDMA_WRITE_IMM 132 
#define  MLX4_OPCODE_SEND_IMM 131 
#define  MLX4_RECV_OPCODE_RDMA_WRITE_IMM 130 
#define  MLX4_RECV_OPCODE_SEND_IMM 129 
#define  MLX4_RECV_OPCODE_SEND_INVAL 128 
 int be32toh (int /*<<< orphan*/ ) ; 
 int htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 struct mlx4_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_cq_read_wc_flags(struct ibv_cq_ex *ibcq)
{
	struct mlx4_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));
	int is_send  = cq->cqe->owner_sr_opcode & MLX4_CQE_IS_SEND_MASK;
	int wc_flags = 0;

	if (is_send) {
		switch (cq->cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) {
		case MLX4_OPCODE_RDMA_WRITE_IMM:
		case MLX4_OPCODE_SEND_IMM:
			wc_flags |= IBV_WC_WITH_IMM;
			break;
		}
	} else {
		if (cq->flags & MLX4_CQ_FLAGS_RX_CSUM_VALID)
			wc_flags |= ((cq->cqe->status &
				htobe32(MLX4_CQE_STATUS_IPV4_CSUM_OK)) ==
				htobe32(MLX4_CQE_STATUS_IPV4_CSUM_OK)) <<
				IBV_WC_IP_CSUM_OK_SHIFT;

		switch (cq->cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) {
		case MLX4_RECV_OPCODE_RDMA_WRITE_IMM:
		case MLX4_RECV_OPCODE_SEND_IMM:
			wc_flags |= IBV_WC_WITH_IMM;
			break;
		case MLX4_RECV_OPCODE_SEND_INVAL:
			wc_flags |= IBV_WC_WITH_INV;
			break;
		}
		wc_flags |= (be32toh(cq->cqe->g_mlpath_rqpn) & 0x80000000) ? IBV_WC_GRH : 0;
	}

	return wc_flags;
}