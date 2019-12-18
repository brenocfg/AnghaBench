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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev_lock; struct net_device* netdev; } ;
struct mlx5_ib_dev {TYPE_1__ roce; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct net_device *mlx5_ib_get_netdev(struct ib_device *device,
					     u8 port_num)
{
	struct mlx5_ib_dev *ibdev = to_mdev(device);
	struct net_device *ndev;

	/* Ensure ndev does not disappear before we invoke dev_hold()
	 */
	read_lock(&ibdev->roce.netdev_lock);
	ndev = ibdev->roce.netdev;
	if (ndev)
		dev_hold(ndev);
	read_unlock(&ibdev->roce.netdev_lock);

	return ndev;
}