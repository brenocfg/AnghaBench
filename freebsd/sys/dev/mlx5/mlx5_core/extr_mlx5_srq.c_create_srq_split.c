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
struct mlx5_srq_attr {int dummy; } ;
struct TYPE_2__ {scalar_t__ res; } ;
struct mlx5_core_srq {TYPE_1__ common; } ;
struct mlx5_core_dev {int /*<<< orphan*/  issi; } ;

/* Variables and functions */
 scalar_t__ MLX5_RES_XSRQ ; 
 int create_rmp_cmd (struct mlx5_core_dev*,struct mlx5_core_srq*,struct mlx5_srq_attr*) ; 
 int create_srq_cmd (struct mlx5_core_dev*,struct mlx5_core_srq*,struct mlx5_srq_attr*) ; 
 int create_xrc_srq_cmd (struct mlx5_core_dev*,struct mlx5_core_srq*,struct mlx5_srq_attr*) ; 

__attribute__((used)) static int create_srq_split(struct mlx5_core_dev *dev, struct mlx5_core_srq *srq,
			    struct mlx5_srq_attr *in)
{
	if (!dev->issi)
		return create_srq_cmd(dev, srq, in);
	else if (srq->common.res == MLX5_RES_XSRQ)
		return create_xrc_srq_cmd(dev, srq, in);
	else
		return create_rmp_cmd(dev, srq, in);
}