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
struct mlx5e_port_eth_proto {int /*<<< orphan*/  oper; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX5_CAP_PCAM_FEATURE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_port_query_eth_proto (struct mlx5_core_dev*,int,int,struct mlx5e_port_eth_proto*) ; 
 int /*<<< orphan*/  mlx5e_port_ptys2speed (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptys_extended_ethernet ; 

int mlx5e_port_linkspeed(struct mlx5_core_dev *mdev, u32 *speed)
{
	struct mlx5e_port_eth_proto eproto;
	bool ext;
	int err;

	ext = MLX5_CAP_PCAM_FEATURE(mdev, ptys_extended_ethernet);
	err = mlx5_port_query_eth_proto(mdev, 1, ext, &eproto);
	if (err)
		goto out;

	*speed = mlx5e_port_ptys2speed(mdev, eproto.oper);
	if (!(*speed))
		err = -EINVAL;

out:
	return err;
}