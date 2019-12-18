#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {TYPE_1__* ports; } ;
struct mlx5_ib_dev {int ib_active; int /*<<< orphan*/  ib_dev; TYPE_2__ devr; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {TYPE_3__ element; int /*<<< orphan*/ * device; int /*<<< orphan*/  event; } ;
typedef  enum mlx5_dev_event { ____Placeholder_mlx5_dev_event } mlx5_dev_event ;
struct TYPE_4__ {int /*<<< orphan*/  pkey_change_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_CLIENT_REREGISTER ; 
 int /*<<< orphan*/  IB_EVENT_DEVICE_FATAL ; 
 int /*<<< orphan*/  IB_EVENT_GID_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_LID_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_PKEY_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 int /*<<< orphan*/  IB_LINK_LAYER_ETHERNET ; 
#define  MLX5_DEV_EVENT_CLIENT_REREG 135 
#define  MLX5_DEV_EVENT_GUID_CHANGE 134 
#define  MLX5_DEV_EVENT_LID_CHANGE 133 
#define  MLX5_DEV_EVENT_PKEY_CHANGE 132 
#define  MLX5_DEV_EVENT_PORT_DOWN 131 
#define  MLX5_DEV_EVENT_PORT_INITIALIZED 130 
#define  MLX5_DEV_EVENT_PORT_UP 129 
#define  MLX5_DEV_EVENT_SYS_ERROR 128 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  mlx5_ib_handle_internal_error (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_port_link_layer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_port_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_ib_event(struct mlx5_core_dev *dev, void *context,
			  enum mlx5_dev_event event, unsigned long param)
{
	struct mlx5_ib_dev *ibdev = (struct mlx5_ib_dev *)context;
	struct ib_event ibev;
	bool fatal = false;
	u8 port = (u8)param;

	switch (event) {
	case MLX5_DEV_EVENT_SYS_ERROR:
		ibev.event = IB_EVENT_DEVICE_FATAL;
		mlx5_ib_handle_internal_error(ibdev);
		fatal = true;
		break;

	case MLX5_DEV_EVENT_PORT_UP:
	case MLX5_DEV_EVENT_PORT_DOWN:
	case MLX5_DEV_EVENT_PORT_INITIALIZED:
		/* In RoCE, port up/down events are handled in
		 * mlx5_netdev_event().
		 */
		if (mlx5_ib_port_link_layer(&ibdev->ib_dev, port) ==
			IB_LINK_LAYER_ETHERNET)
			return;

		ibev.event = (event == MLX5_DEV_EVENT_PORT_UP) ?
			     IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;
		break;

	case MLX5_DEV_EVENT_LID_CHANGE:
		ibev.event = IB_EVENT_LID_CHANGE;
		break;

	case MLX5_DEV_EVENT_PKEY_CHANGE:
		ibev.event = IB_EVENT_PKEY_CHANGE;

		schedule_work(&ibdev->devr.ports[port - 1].pkey_change_work);
		break;

	case MLX5_DEV_EVENT_GUID_CHANGE:
		ibev.event = IB_EVENT_GID_CHANGE;
		break;

	case MLX5_DEV_EVENT_CLIENT_REREG:
		ibev.event = IB_EVENT_CLIENT_REREGISTER;
		break;

	default:
		/* unsupported event */
		return;
	}

	ibev.device	      = &ibdev->ib_dev;
	ibev.element.port_num = port;

	if (!rdma_is_port_valid(&ibdev->ib_dev, port)) {
		mlx5_ib_warn(ibdev, "warning: event(%d) on port %d\n", event, port);
		return;
	}

	if (ibdev->ib_active)
		ib_dispatch_event(&ibev);

	if (fatal)
		ibdev->ib_active = false;
}