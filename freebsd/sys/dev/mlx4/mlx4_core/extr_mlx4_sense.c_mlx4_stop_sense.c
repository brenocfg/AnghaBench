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
struct mlx4_sense {int gone; int /*<<< orphan*/  sense_poll; } ;
struct mlx4_priv {struct mlx4_sense sense; int /*<<< orphan*/  port_mutex; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx4_stop_sense(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_sense *sense = &priv->sense;

	mutex_lock(&priv->port_mutex);
	sense->gone = 1;
	mutex_unlock(&priv->port_mutex);

	cancel_delayed_work_sync(&mlx4_priv(dev)->sense.sense_poll);
}