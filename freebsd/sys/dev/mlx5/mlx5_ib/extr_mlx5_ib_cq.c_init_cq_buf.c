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
struct mlx5_ib_cq_buf {int nent; int cqe_size; } ;
struct mlx5_ib_cq {int dummy; } ;
struct mlx5_cqe64 {int op_own; } ;

/* Variables and functions */
 int MLX5_CQE_INVALID ; 
 void* get_cqe_from_buf (struct mlx5_ib_cq_buf*,int,int) ; 

__attribute__((used)) static void init_cq_buf(struct mlx5_ib_cq *cq, struct mlx5_ib_cq_buf *buf)
{
	int i;
	void *cqe;
	struct mlx5_cqe64 *cqe64;

	for (i = 0; i < buf->nent; i++) {
		cqe = get_cqe_from_buf(buf, i, buf->cqe_size);
		cqe64 = buf->cqe_size == 64 ? cqe : cqe + 64;
		cqe64->op_own = MLX5_CQE_INVALID << 4;
	}
}