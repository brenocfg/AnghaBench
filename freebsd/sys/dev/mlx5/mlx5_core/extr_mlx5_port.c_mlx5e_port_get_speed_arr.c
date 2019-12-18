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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int MLX5_CAP_PCAM_FEATURE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx5e_ext_link_speed ; 
 int /*<<< orphan*/ * mlx5e_link_speed ; 
 int /*<<< orphan*/  ptys_extended_ethernet ; 

__attribute__((used)) static void mlx5e_port_get_speed_arr(struct mlx5_core_dev *mdev,
				     const u32 **arr, u32 *size)
{
	bool ext = MLX5_CAP_PCAM_FEATURE(mdev, ptys_extended_ethernet);

	*size = ext ? ARRAY_SIZE(mlx5e_ext_link_speed) :
		      ARRAY_SIZE(mlx5e_link_speed);
	*arr  = ext ? mlx5e_ext_link_speed : mlx5e_link_speed;
}