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
struct TYPE_2__ {int /*<<< orphan*/  num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_active_ports mlx4_get_active_ports (struct mlx4_dev*,int) ; 

__attribute__((used)) static int mlx4_slaves_closest_port(struct mlx4_dev *dev, int slave, int port)
{
	struct mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);
	int min_port = find_first_bit(actv_ports.ports, dev->caps.num_ports)
			+ 1;
	int max_port = min_port +
		bitmap_weight(actv_ports.ports, dev->caps.num_ports);

	if (port < min_port)
		port = min_port;
	else if (port >= max_port)
		port = max_port - 1;

	return port;
}