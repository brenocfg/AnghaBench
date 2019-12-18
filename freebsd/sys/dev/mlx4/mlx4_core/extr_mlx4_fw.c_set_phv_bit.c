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
typedef  size_t u8 ;
struct TYPE_2__ {int flags2; int* phv_bit; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 int MLX4_DEV_CAP_FLAG2_PHV_EN ; 
 int MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN ; 
 int mlx4_SET_PORT_phv_bit (struct mlx4_dev*,size_t,int) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 

int set_phv_bit(struct mlx4_dev *dev, u8 port, int new_val)
{
	int ret;

	if (mlx4_is_slave(dev))
		return -EPERM;

	if (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PHV_EN &&
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN)) {
		ret = mlx4_SET_PORT_phv_bit(dev, port, new_val);
		if (!ret)
			dev->caps.phv_bit[port] = new_val;
		return ret;
	}

	return -EOPNOTSUPP;
}