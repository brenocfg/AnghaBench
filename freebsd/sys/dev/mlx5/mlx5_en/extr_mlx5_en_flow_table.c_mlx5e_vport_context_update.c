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
struct mlx5e_eth_addr_db {int /*<<< orphan*/  promisc_enabled; int /*<<< orphan*/  allmulti_enabled; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct mlx5e_eth_addr_db eth_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_NIC_VPORT_LIST_TYPE_MC ; 
 int /*<<< orphan*/  MLX5_NIC_VPORT_LIST_TYPE_UC ; 
 int /*<<< orphan*/  mlx5_modify_nic_vport_promisc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_vport_context_update_addr_list (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_vport_context_update(struct mlx5e_priv *priv)
{
	struct mlx5e_eth_addr_db *ea = &priv->eth_addr;

	mlx5e_vport_context_update_addr_list(priv, MLX5_NIC_VPORT_LIST_TYPE_UC);
	mlx5e_vport_context_update_addr_list(priv, MLX5_NIC_VPORT_LIST_TYPE_MC);
	mlx5_modify_nic_vport_promisc(priv->mdev, 0,
				      ea->allmulti_enabled,
				      ea->promisc_enabled);
}