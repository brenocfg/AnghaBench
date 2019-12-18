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
typedef  int u8 ;
struct mlx4_ib_dev {int bond_next_port; int num_ports; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 mlx4_ib_bond_next_port(struct mlx4_ib_dev *dev)
{
	dev->bond_next_port = (dev->bond_next_port + 1) % dev->num_ports;

	return dev->bond_next_port + 1;
}