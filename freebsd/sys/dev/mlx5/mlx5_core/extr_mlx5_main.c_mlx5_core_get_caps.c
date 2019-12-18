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
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_cap_type { ____Placeholder_mlx5_cap_type } mlx5_cap_type ;

/* Variables and functions */
 int /*<<< orphan*/  HCA_CAP_OPMOD_GET_CUR ; 
 int /*<<< orphan*/  HCA_CAP_OPMOD_GET_MAX ; 
 int mlx5_core_get_caps_mode (struct mlx5_core_dev*,int,int /*<<< orphan*/ ) ; 

int mlx5_core_get_caps(struct mlx5_core_dev *dev, enum mlx5_cap_type cap_type)
{
	int ret;

	ret = mlx5_core_get_caps_mode(dev, cap_type, HCA_CAP_OPMOD_GET_CUR);
	if (ret)
		return ret;

	return mlx5_core_get_caps_mode(dev, cap_type, HCA_CAP_OPMOD_GET_MAX);
}