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
typedef  int /*<<< orphan*/  u8 ;
struct ib_port_attr {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MLX5_VPORT_ACCESS_METHOD_HCA 130 
#define  MLX5_VPORT_ACCESS_METHOD_MAD 129 
#define  MLX5_VPORT_ACCESS_METHOD_NIC 128 
 int mlx5_get_vport_access_method (struct ib_device*) ; 
 int mlx5_query_hca_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 int mlx5_query_mad_ifc_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 int mlx5_query_port_roce (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

int mlx5_ib_query_port(struct ib_device *ibdev, u8 port,
		       struct ib_port_attr *props)
{
	switch (mlx5_get_vport_access_method(ibdev)) {
	case MLX5_VPORT_ACCESS_METHOD_MAD:
		return mlx5_query_mad_ifc_port(ibdev, port, props);

	case MLX5_VPORT_ACCESS_METHOD_HCA:
		return mlx5_query_hca_port(ibdev, port, props);

	case MLX5_VPORT_ACCESS_METHOD_NIC:
		return mlx5_query_port_roce(ibdev, port, props);

	default:
		return -EINVAL;
	}
}