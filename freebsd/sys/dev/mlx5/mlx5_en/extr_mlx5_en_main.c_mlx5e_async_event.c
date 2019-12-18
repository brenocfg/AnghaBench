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
struct mlx5e_priv {int /*<<< orphan*/  async_events_mtx; int /*<<< orphan*/  state; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_dev_event { ____Placeholder_mlx5_dev_event } mlx5_dev_event ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_ASYNC_EVENTS_ENABLE ; 
 int /*<<< orphan*/  mlx5e_async_event_sub (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_async_event(struct mlx5_core_dev *mdev, void *vpriv,
    enum mlx5_dev_event event, unsigned long param)
{
	struct mlx5e_priv *priv = vpriv;

	mtx_lock(&priv->async_events_mtx);
	if (test_bit(MLX5E_STATE_ASYNC_EVENTS_ENABLE, &priv->state))
		mlx5e_async_event_sub(priv, event);
	mtx_unlock(&priv->async_events_mtx);
}