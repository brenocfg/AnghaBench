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
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
struct mlx4_dev {scalar_t__* regid_promisc_array; scalar_t__* regid_allmulti_array; } ;
typedef  enum mlx4_net_trans_promisc_mode { ____Placeholder_mlx4_net_trans_promisc_mode } mlx4_net_trans_promisc_mode ;

/* Variables and functions */
#define  MLX4_FS_ALL_DEFAULT 129 
#define  MLX4_FS_MC_DEFAULT 128 
 int mlx4_flow_detach (struct mlx4_dev*,scalar_t__) ; 

int mlx4_flow_steer_promisc_remove(struct mlx4_dev *dev, u8 port,
				   enum mlx4_net_trans_promisc_mode mode)
{
	int ret;
	u64 *regid_p;

	switch (mode) {
	case MLX4_FS_ALL_DEFAULT:
		regid_p = &dev->regid_promisc_array[port];
		break;
	case MLX4_FS_MC_DEFAULT:
		regid_p = &dev->regid_allmulti_array[port];
		break;
	default:
		return -1;
	}

	if (*regid_p == 0)
		return -1;

	ret =  mlx4_flow_detach(dev, *regid_p);
	if (ret == 0)
		*regid_p = 0;

	return ret;
}