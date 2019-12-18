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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_qp {int /*<<< orphan*/  qpn; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RES_RQ ; 
 int create_qprqsq_common (struct mlx5_core_dev*,struct mlx5_core_qp*,int /*<<< orphan*/ ) ; 
 int mlx5_core_create_rq (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_destroy_rq (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

int mlx5_core_create_rq_tracked(struct mlx5_core_dev *dev, u32 *in, int inlen,
				struct mlx5_core_qp *rq)
{
	int err;

	err = mlx5_core_create_rq(dev, in, inlen, &rq->qpn);
	if (err)
		return err;

	err = create_qprqsq_common(dev, rq, MLX5_RES_RQ);
	if (err)
		mlx5_core_destroy_rq(dev, rq->qpn);

	return err;
}