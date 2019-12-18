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
struct TYPE_2__ {int num_ports; scalar_t__* port_type; int flags; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  EN_DRV_NAME ; 
 int /*<<< orphan*/  IB_DRV_NAME ; 
 int MLX4_DEV_CAP_FLAG_IBOE ; 
 scalar_t__ MLX4_PORT_TYPE_ETH ; 
 scalar_t__ MLX4_PORT_TYPE_IB ; 
 int /*<<< orphan*/  request_module_nowait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_request_modules(struct mlx4_dev *dev)
{
	int port;
	int has_ib_port = false;
	int has_eth_port = false;
#define EN_DRV_NAME	"mlx4_en"
#define IB_DRV_NAME	"mlx4_ib"

	for (port = 1; port <= dev->caps.num_ports; port++) {
		if (dev->caps.port_type[port] == MLX4_PORT_TYPE_IB)
			has_ib_port = true;
		else if (dev->caps.port_type[port] == MLX4_PORT_TYPE_ETH)
			has_eth_port = true;
	}

	if (has_eth_port)
		request_module_nowait(EN_DRV_NAME);
	if (has_ib_port || (dev->caps.flags & MLX4_DEV_CAP_FLAG_IBOE))
		request_module_nowait(IB_DRV_NAME);
}