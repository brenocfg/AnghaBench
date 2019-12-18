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
struct net_device {int if_mtu; int if_drv_flags; } ;
struct mlx4_en_priv {int max_mtu; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  device_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int EPERM ; 
 int IFF_DRV_RUNNING ; 
 int MLX4_EN_MIN_MTU ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,int,...) ; 
 int mlx4_en_start_port (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx4_en_change_mtu(struct net_device *dev, int new_mtu)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int err = 0;

	en_dbg(DRV, priv, "Change MTU called - current:%u new:%u\n",
	       (unsigned)dev->if_mtu, (unsigned)new_mtu);

	if ((new_mtu < MLX4_EN_MIN_MTU) || (new_mtu > priv->max_mtu)) {
		en_err(priv, "Bad MTU size:%d, max %u.\n", new_mtu,
		    priv->max_mtu);
		return -EPERM;
	}
	mutex_lock(&mdev->state_lock);
	dev->if_mtu = new_mtu;
	if (dev->if_drv_flags & IFF_DRV_RUNNING) {
		if (!mdev->device_up) {
			/* NIC is probably restarting - let watchdog task reset
			 *                          * the port */
			en_dbg(DRV, priv, "Change MTU called with card down!?\n");
		} else {
			mlx4_en_stop_port(dev);
			err = mlx4_en_start_port(dev);
			if (err) {
				en_err(priv, "Failed restarting port:%d\n",
						priv->port);
				queue_work(mdev->workqueue, &priv->watchdog_task);
			}
		}
	}
	mutex_unlock(&mdev->state_lock);
	return 0;
}