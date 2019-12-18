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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int num_ports; scalar_t__* port_type; int /*<<< orphan*/ * def_mac; } ;
struct mlx4_dev {int port_random_macs; TYPE_1__ caps; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ MLX4_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  mlx4_mac_to_u64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ *) ; 

void mlx4_replace_zero_macs(struct mlx4_dev *dev)
{
	int i;
	u8 mac_addr[ETH_ALEN];

	dev->port_random_macs = 0;
	for (i = 1; i <= dev->caps.num_ports; ++i)
		if (!dev->caps.def_mac[i] &&
		    dev->caps.port_type[i] == MLX4_PORT_TYPE_ETH) {
			random_ether_addr(mac_addr);
			dev->port_random_macs |= 1 << i;
			dev->caps.def_mac[i] = mlx4_mac_to_u64(mac_addr);
		}
}