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
struct net_device {int dummy; } ;
struct mlx4_en_priv {size_t port; int gone; struct mlx4_en_priv* tx_cq; struct mlx4_en_priv* tx_ring; int /*<<< orphan*/  conf_ctx; int /*<<< orphan*/ * conf_sysctl; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  service_task; int /*<<< orphan*/  stats_task; int /*<<< orphan*/  res; scalar_t__ allocated; scalar_t__ registered; int /*<<< orphan*/ * vlan_detach; int /*<<< orphan*/ * vlan_attach; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/ ** pndev; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX4_EN_PAGE_SIZE ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,size_t) ; 
 int /*<<< orphan*/  ether_ifdetach (struct net_device*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_free (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_free_resources (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

void mlx4_en_destroy_netdev(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;

	en_dbg(DRV, priv, "Destroying netdev on port:%d\n", priv->port);

	/* don't allow more IOCTLs */
	priv->gone = 1;

	/* XXX wait a bit to allow IOCTL handlers to complete */
	pause("W", hz);

	if (priv->vlan_attach != NULL)
		EVENTHANDLER_DEREGISTER(vlan_config, priv->vlan_attach);
	if (priv->vlan_detach != NULL)
		EVENTHANDLER_DEREGISTER(vlan_unconfig, priv->vlan_detach);

	mutex_lock(&mdev->state_lock);
	mlx4_en_stop_port(dev);
	mutex_unlock(&mdev->state_lock);

	/* Unregister device - this will close the port if it was up */
	if (priv->registered)
		ether_ifdetach(dev);

	if (priv->allocated)
		mlx4_free_hwq_res(mdev->dev, &priv->res, MLX4_EN_PAGE_SIZE);

	cancel_delayed_work(&priv->stats_task);
	cancel_delayed_work(&priv->service_task);
	/* flush any pending task for this netdev */
	flush_workqueue(mdev->workqueue);
        callout_drain(&priv->watchdog_timer);

	/* Detach the netdev so tasks would not attempt to access it */
	mutex_lock(&mdev->state_lock);
	mdev->pndev[priv->port] = NULL;
	mutex_unlock(&mdev->state_lock);


	mlx4_en_free_resources(priv);

	/* freeing the sysctl conf cannot be called from within mlx4_en_free_resources */
	if (priv->conf_sysctl != NULL)
		sysctl_ctx_free(&priv->conf_ctx);

	kfree(priv->tx_ring);
	kfree(priv->tx_cq);

        kfree(priv);
        if_free(dev);

}