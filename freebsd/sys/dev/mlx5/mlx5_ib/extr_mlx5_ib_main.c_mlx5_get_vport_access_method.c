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
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_ETHERNET ; 
 int MLX5_VPORT_ACCESS_METHOD_HCA ; 
 int MLX5_VPORT_ACCESS_METHOD_MAD ; 
 int MLX5_VPORT_ACCESS_METHOD_NIC ; 
 scalar_t__ mlx5_ib_port_link_layer (struct ib_device*,int) ; 
 scalar_t__ mlx5_use_mad_ifc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mlx5_get_vport_access_method(struct ib_device *ibdev)
{
	if (mlx5_use_mad_ifc(to_mdev(ibdev)))
		return MLX5_VPORT_ACCESS_METHOD_MAD;

	if (mlx5_ib_port_link_layer(ibdev, 1) ==
	    IB_LINK_LAYER_ETHERNET)
		return MLX5_VPORT_ACCESS_METHOD_NIC;

	return MLX5_VPORT_ACCESS_METHOD_HCA;
}