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
struct mlx4_en_priv {int link_state; int /*<<< orphan*/  linkstate_task; } ;
struct mlx4_en_dev {int /*<<< orphan*/ * pndev; int /*<<< orphan*/  workqueue; } ;
struct TYPE_2__ {unsigned long num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
typedef  enum mlx4_dev_event { ____Placeholder_mlx4_dev_event } mlx4_dev_event ;

/* Variables and functions */
#define  MLX4_DEV_EVENT_CATASTROPHIC_ERROR 132 
#define  MLX4_DEV_EVENT_PORT_DOWN 131 
#define  MLX4_DEV_EVENT_PORT_UP 130 
#define  MLX4_DEV_EVENT_SLAVE_INIT 129 
#define  MLX4_DEV_EVENT_SLAVE_SHUTDOWN 128 
 int /*<<< orphan*/  mlx4_err (struct mlx4_en_dev*,char*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_en_dev*,char*,int,int) ; 
 struct mlx4_en_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_en_event(struct mlx4_dev *dev, void *endev_ptr,
			  enum mlx4_dev_event event, unsigned long port)
{
	struct mlx4_en_dev *mdev = (struct mlx4_en_dev *) endev_ptr;
	struct mlx4_en_priv *priv;

	switch (event) {
	case MLX4_DEV_EVENT_PORT_UP:
	case MLX4_DEV_EVENT_PORT_DOWN:
		if (!mdev->pndev[port])
			return;
		priv = netdev_priv(mdev->pndev[port]);
		/* To prevent races, we poll the link state in a separate
		  task rather than changing it here */
		priv->link_state = event;
		queue_work(mdev->workqueue, &priv->linkstate_task);
		break;

	case MLX4_DEV_EVENT_CATASTROPHIC_ERROR:
		mlx4_err(mdev, "Internal error detected, restarting device\n");
		break;

	case MLX4_DEV_EVENT_SLAVE_INIT:
	case MLX4_DEV_EVENT_SLAVE_SHUTDOWN:
		break;
	default:
		if (port < 1 || port > dev->caps.num_ports ||
		    !mdev->pndev[port])
			return;
		mlx4_warn(mdev, "Unhandled event %d for port %d\n", event,
			  (int) port);
	}
}