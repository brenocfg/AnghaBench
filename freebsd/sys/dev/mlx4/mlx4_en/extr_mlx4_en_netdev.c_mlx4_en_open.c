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
struct mlx4_en_priv {int /*<<< orphan*/  port; struct net_device* dev; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  device_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  mlx4_en_clear_stats (struct net_device*) ; 
 int mlx4_en_start_port (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_en_open(void* arg)
{

        struct mlx4_en_priv *priv;
        struct mlx4_en_dev *mdev;
        struct net_device *dev;
        int err = 0;

        priv = arg;
        mdev = priv->mdev;
        dev = priv->dev;


	mutex_lock(&mdev->state_lock);

	if (!mdev->device_up) {
		en_err(priv, "Cannot open - device down/disabled\n");
		goto out;
	}

	/* Reset HW statistics and SW counters */
	mlx4_en_clear_stats(dev);

	err = mlx4_en_start_port(dev);
	if (err)
		en_err(priv, "Failed starting port:%d\n", priv->port);

out:
	mutex_unlock(&mdev->state_lock);
	return;
}