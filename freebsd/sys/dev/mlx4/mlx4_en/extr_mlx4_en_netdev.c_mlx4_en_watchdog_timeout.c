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
struct mlx4_en_priv {int /*<<< orphan*/  watchdog_timer; scalar_t__ port_up; int /*<<< orphan*/  watchdog_task; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  MLX4_EN_WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_en_watchdog_timeout(void *arg)
{
        struct mlx4_en_priv *priv = arg;
        struct mlx4_en_dev *mdev = priv->mdev;

        en_dbg(DRV, priv, "Scheduling watchdog\n");
        queue_work(mdev->workqueue, &priv->watchdog_task);
        if (priv->port_up)
                callout_reset(&priv->watchdog_timer, MLX4_EN_WATCHDOG_TIMEOUT,
                                mlx4_en_watchdog_timeout, priv);
}