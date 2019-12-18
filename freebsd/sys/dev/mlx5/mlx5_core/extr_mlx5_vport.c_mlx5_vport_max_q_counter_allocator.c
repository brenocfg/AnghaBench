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
typedef  scalar_t__ u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
#define  MLX5_INTERFACE_PROTOCOL_ETH 129 
#define  MLX5_INTERFACE_PROTOCOL_IB 128 
 scalar_t__ MLX5_QCOUNTER_SETS_NETDEV ; 
 int /*<<< orphan*/  max_qp_cnt ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 

__attribute__((used)) static u32 mlx5_vport_max_q_counter_allocator(struct mlx5_core_dev *mdev,
					      int client_id)
{
	switch (client_id) {
	case MLX5_INTERFACE_PROTOCOL_IB:
		return (MLX5_CAP_GEN(mdev, max_qp_cnt) -
			MLX5_QCOUNTER_SETS_NETDEV);
	case MLX5_INTERFACE_PROTOCOL_ETH:
		return MLX5_QCOUNTER_SETS_NETDEV;
	default:
		mlx5_core_warn(mdev, "Unknown Client: %d\n", client_id);
		return 0;
	}
}