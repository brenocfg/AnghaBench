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
struct net_device {int dummy; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_PROT_ETH ; 
 struct net_device* bond_option_active_slave_get_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net_device* mlx4_get_protocol_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_bonded (int /*<<< orphan*/ ) ; 
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct net_device *mlx4_ib_get_netdev(struct ib_device *device, u8 port_num)
{
	struct mlx4_ib_dev *ibdev = to_mdev(device);
	struct net_device *dev;

	rcu_read_lock();
	dev = mlx4_get_protocol_dev(ibdev->dev, MLX4_PROT_ETH, port_num);

#if 0
	if (dev) {
		if (mlx4_is_bonded(ibdev->dev)) {
			struct net_device *upper = NULL;

			upper = netdev_master_upper_dev_get_rcu(dev);
			if (upper) {
				struct net_device *active;

				active = bond_option_active_slave_get_rcu(netdev_priv(upper));
				if (active)
					dev = active;
			}
		}
	}
#endif
	if (dev)
		dev_hold(dev);

	rcu_read_unlock();
	return dev;
}