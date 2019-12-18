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
struct mlx5_cqe64 {int op_own; } ;
struct TYPE_2__ {int cqe; } ;
struct mlx5_cq {int cqe_sz; TYPE_1__ ibv_cq; } ;

/* Variables and functions */
 scalar_t__ MLX5_CQE_INVALID ; 
 int MLX5_CQE_OWNER_MASK ; 
 void* get_cqe (struct mlx5_cq*,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ mlx5dv_get_cqe_opcode (struct mlx5_cqe64*) ; 

__attribute__((used)) static void *get_sw_cqe(struct mlx5_cq *cq, int n)
{
	void *cqe = get_cqe(cq, n & cq->ibv_cq.cqe);
	struct mlx5_cqe64 *cqe64;

	cqe64 = (cq->cqe_sz == 64) ? cqe : cqe + 64;

	if (likely(mlx5dv_get_cqe_opcode(cqe64) != MLX5_CQE_INVALID) &&
	    !((cqe64->op_own & MLX5_CQE_OWNER_MASK) ^ !!(n & (cq->ibv_cq.cqe + 1)))) {
		return cqe;
	} else {
		return NULL;
	}
}