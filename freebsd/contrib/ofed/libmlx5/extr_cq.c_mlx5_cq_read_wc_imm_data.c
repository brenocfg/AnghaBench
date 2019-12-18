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
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx5_cq {TYPE_1__* cqe64; } ;
struct ibv_cq_ex {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  imm_inval_pkey; } ;

/* Variables and functions */
#define  MLX5_CQE_RESP_SEND_INV 128 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 int mlx5dv_get_cqe_opcode (TYPE_1__*) ; 
 struct mlx5_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t mlx5_cq_read_wc_imm_data(struct ibv_cq_ex *ibcq)
{
	struct mlx5_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));

	switch (mlx5dv_get_cqe_opcode(cq->cqe64)) {
	case MLX5_CQE_RESP_SEND_INV:
		return be32toh(cq->cqe64->imm_inval_pkey);
	default:
		return cq->cqe64->imm_inval_pkey;
	}
}