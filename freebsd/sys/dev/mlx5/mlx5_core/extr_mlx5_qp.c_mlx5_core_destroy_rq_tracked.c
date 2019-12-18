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
struct mlx5_core_qp {int /*<<< orphan*/  qpn; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RES_RQ ; 
 int /*<<< orphan*/  destroy_qprqsq_common (struct mlx5_core_dev*,struct mlx5_core_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_rq (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

void mlx5_core_destroy_rq_tracked(struct mlx5_core_dev *dev,
				  struct mlx5_core_qp *rq)
{
	destroy_qprqsq_common(dev, rq, MLX5_RES_RQ);
	mlx5_core_destroy_rq(dev, rq->qpn);
}