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
struct mlx5_core_rsc_common {int res; } ;
struct mlx5_core_qp {int /*<<< orphan*/  (* event ) (struct mlx5_core_qp*,int) ;} ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
#define  MLX5_RES_QP 128 
 int /*<<< orphan*/  mlx5_core_put_rsc (struct mlx5_core_rsc_common*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 struct mlx5_core_rsc_common* mlx5_get_rsc (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_qp*,int) ; 

void mlx5_rsc_event(struct mlx5_core_dev *dev, u32 rsn, int event_type)
{
	struct mlx5_core_rsc_common *common = mlx5_get_rsc(dev, rsn);
	struct mlx5_core_qp *qp;

	if (!common)
		return;

	switch (common->res) {
	case MLX5_RES_QP:
		qp = (struct mlx5_core_qp *)common;
		qp->event(qp, event_type);
		break;

	default:
		mlx5_core_warn(dev, "invalid resource type for 0x%x\n", rsn);
	}

	mlx5_core_put_rsc(common);
}