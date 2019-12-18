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
struct mlx5_eqe_port_module_event {scalar_t__ error_type; scalar_t__ module_status; scalar_t__ module; } ;
struct TYPE_4__ {struct mlx5_eqe_port_module_event port_module_event; } ;
struct mlx5_eqe {TYPE_1__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * error_counters; int /*<<< orphan*/ * status_counters; } ;
struct TYPE_6__ {TYPE_2__ pme_stats; } ;
struct mlx5_core_dev {unsigned int* module_status; TYPE_3__ priv; } ;

/* Variables and functions */
 unsigned int MLX5_MAX_PORTS ; 
 unsigned int MLX5_MODULE_EVENT_ERROR_NUM ; 
#define  MLX5_MODULE_STATUS_ERROR 130 
 unsigned int MLX5_MODULE_STATUS_NUM ; 
#define  MLX5_MODULE_STATUS_PLUGGED_ENABLED 129 
#define  MLX5_MODULE_STATUS_UNPLUGGED 128 
 unsigned int PORT_MODULE_EVENT_ERROR_TYPE_MASK ; 
 unsigned int PORT_MODULE_EVENT_MODULE_STATUS_MASK ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  mlx5_port_module_event_error_type_to_string (unsigned int) ; 

__attribute__((used)) static void mlx5_port_module_event(struct mlx5_core_dev *dev,
				   struct mlx5_eqe *eqe)
{
	unsigned int module_num;
	unsigned int module_status;
	unsigned int error_type;
	struct mlx5_eqe_port_module_event *module_event_eqe;

	module_event_eqe = &eqe->data.port_module_event;

	module_num = (unsigned int)module_event_eqe->module;
	module_status = (unsigned int)module_event_eqe->module_status &
	    PORT_MODULE_EVENT_MODULE_STATUS_MASK;
	error_type = (unsigned int)module_event_eqe->error_type &
	    PORT_MODULE_EVENT_ERROR_TYPE_MASK;

	if (module_status < MLX5_MODULE_STATUS_NUM)
		dev->priv.pme_stats.status_counters[module_status]++;
	switch (module_status) {
	case MLX5_MODULE_STATUS_PLUGGED_ENABLED:
		mlx5_core_info(dev,
		    "Module %u, status: plugged and enabled\n",
		    module_num);
		break;

	case MLX5_MODULE_STATUS_UNPLUGGED:
		mlx5_core_info(dev,
		    "Module %u, status: unplugged\n", module_num);
		break;

	case MLX5_MODULE_STATUS_ERROR:
		mlx5_core_err(dev,
		    "Module %u, status: error, %s (%d)\n",
		    module_num,
		    mlx5_port_module_event_error_type_to_string(error_type),
		    error_type);
		if (error_type < MLX5_MODULE_EVENT_ERROR_NUM)
			dev->priv.pme_stats.error_counters[error_type]++;
		break;

	default:
		mlx5_core_info(dev,
		    "Module %u, unknown status %d\n", module_num, module_status);
	}
	/* store module status */
	if (module_num < MLX5_MAX_PORTS)
		dev->module_status[module_num] = module_status;
}