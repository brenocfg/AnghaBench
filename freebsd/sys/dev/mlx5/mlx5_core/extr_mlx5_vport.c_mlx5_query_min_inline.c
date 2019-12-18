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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
#define  MLX5_CAP_INLINE_MODE_L2 130 
#define  MLX5_CAP_INLINE_MODE_NOT_REQUIRED 129 
#define  MLX5_CAP_INLINE_MODE_VPORT_CONTEXT 128 
 int /*<<< orphan*/  MLX5_INLINE_MODE_L2 ; 
 int /*<<< orphan*/  MLX5_INLINE_MODE_NONE ; 
 int mlx5_query_nic_vport_min_inline (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wqe_inline_mode ; 

int mlx5_query_min_inline(struct mlx5_core_dev *mdev,
			  u8 *min_inline_mode)
{
	int err;

	switch (MLX5_CAP_ETH(mdev, wqe_inline_mode)) {
	case MLX5_CAP_INLINE_MODE_L2:
		*min_inline_mode = MLX5_INLINE_MODE_L2;
		err = 0;
		break;
	case MLX5_CAP_INLINE_MODE_VPORT_CONTEXT:
		err = mlx5_query_nic_vport_min_inline(mdev, 0, min_inline_mode);
		break;
	case MLX5_CAP_INLINE_MODE_NOT_REQUIRED:
		*min_inline_mode = MLX5_INLINE_MODE_NONE;
		err = 0;
		break;
	default:
		err = -EINVAL;
		break;
	}
	return err;
}