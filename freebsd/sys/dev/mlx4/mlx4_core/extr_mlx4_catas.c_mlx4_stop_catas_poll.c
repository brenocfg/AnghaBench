#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * map; int /*<<< orphan*/  timer; } ;
struct mlx4_priv {TYPE_1__ catas_err; } ;
struct mlx4_dev {TYPE_2__* persist; } ;
struct TYPE_4__ {int interface_state; int /*<<< orphan*/  catas_wq; } ;

/* Variables and functions */
 int MLX4_INTERFACE_STATE_DELETION ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_stop_catas_poll(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	del_timer_sync(&priv->catas_err.timer);

	if (priv->catas_err.map) {
		iounmap(priv->catas_err.map);
		priv->catas_err.map = NULL;
	}

	if (dev->persist->interface_state & MLX4_INTERFACE_STATE_DELETION)
		flush_workqueue(dev->persist->catas_wq);
}