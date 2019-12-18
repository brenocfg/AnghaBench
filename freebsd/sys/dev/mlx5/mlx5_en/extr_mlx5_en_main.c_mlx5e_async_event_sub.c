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
struct mlx5e_priv {int /*<<< orphan*/  update_carrier_work; int /*<<< orphan*/  wq; } ;
typedef  enum mlx5_dev_event { ____Placeholder_mlx5_dev_event } mlx5_dev_event ;

/* Variables and functions */
#define  MLX5_DEV_EVENT_PORT_DOWN 129 
#define  MLX5_DEV_EVENT_PORT_UP 128 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_async_event_sub(struct mlx5e_priv *priv,
    enum mlx5_dev_event event)
{
	switch (event) {
	case MLX5_DEV_EVENT_PORT_UP:
	case MLX5_DEV_EVENT_PORT_DOWN:
		queue_work(priv->wq, &priv->update_carrier_work);
		break;

	default:
		break;
	}
}