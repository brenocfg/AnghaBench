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
struct mlx5e_cq {int /*<<< orphan*/  wq; } ;
struct mlx5_cqe64 {int op_own; } ;

/* Variables and functions */
 int MLX5_CQE_OWNER_MASK ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 int /*<<< orphan*/  mlx5_cqwq_get_ci (int /*<<< orphan*/ *) ; 
 struct mlx5_cqe64* mlx5_cqwq_get_wqe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mlx5_cqwq_get_wrap_cnt (int /*<<< orphan*/ *) ; 

struct mlx5_cqe64 *
mlx5e_get_cqe(struct mlx5e_cq *cq)
{
	struct mlx5_cqe64 *cqe;

	cqe = mlx5_cqwq_get_wqe(&cq->wq, mlx5_cqwq_get_ci(&cq->wq));

	if ((cqe->op_own ^ mlx5_cqwq_get_wrap_cnt(&cq->wq)) & MLX5_CQE_OWNER_MASK)
		return (NULL);

	/* ensure cqe content is read after cqe ownership bit */
	atomic_thread_fence_acq();

	return (cqe);
}