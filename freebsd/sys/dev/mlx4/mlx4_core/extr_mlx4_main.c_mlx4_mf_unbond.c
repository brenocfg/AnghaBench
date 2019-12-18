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
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int mlx4_unbond_fs_rules (struct mlx4_dev*) ; 
 int mlx4_unbond_mac_table (struct mlx4_dev*) ; 
 int mlx4_unbond_vlan_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int) ; 

__attribute__((used)) static int mlx4_mf_unbond(struct mlx4_dev *dev)
{
	int ret, ret1;

	ret = mlx4_unbond_fs_rules(dev);
	if (ret)
		mlx4_warn(dev, "multifunction unbond for flow rules failedi (%d)\n", ret);
	ret1 = mlx4_unbond_mac_table(dev);
	if (ret1) {
		mlx4_warn(dev, "multifunction unbond for MAC table failed (%d)\n", ret1);
		ret = ret1;
	}
	ret1 = mlx4_unbond_vlan_table(dev);
	if (ret1) {
		mlx4_warn(dev, "multifunction unbond for VLAN table failed (%d)\n", ret1);
		ret = ret1;
	}
	return ret;
}