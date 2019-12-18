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
struct mlx5e_priv {int /*<<< orphan*/  watchdog; int /*<<< orphan*/  update_stats_work; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct mlx5e_priv*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_update_stats(void *arg)
{
	struct mlx5e_priv *priv = arg;

	queue_work(priv->wq, &priv->update_stats_work);

	callout_reset(&priv->watchdog, hz, &mlx5e_update_stats, priv);
}