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
 int /*<<< orphan*/  MLX5_RES_SQ ; 
 int create_qprqsq_common (struct mlx5_core_dev*,struct mlx5_core_qp*,int /*<<< orphan*/ ) ; 
 int mlx5_core_create_sq (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_destroy_sq (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

int mlx5_core_create_sq_tracked(struct mlx5_core_dev *dev, u32 *in, int inlen,
				struct mlx5_core_qp *sq)
{
	int err;

	err = mlx5_core_create_sq(dev, in, inlen, &sq->qpn);
	if (err)
		return err;

	err = create_qprqsq_common(dev, sq, MLX5_RES_SQ);
	if (err)
		mlx5_core_destroy_sq(dev, sq->qpn);

	return err;
}