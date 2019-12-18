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
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct mlx5e_eth_addr_hash_node {int action; unsigned int mpfs_index; int /*<<< orphan*/  ai; } ;

/* Variables and functions */
#define  MLX5E_ACTION_ADD 129 
#define  MLX5E_ACTION_DEL 128 
 int MLX5E_ACTION_NONE ; 
 int /*<<< orphan*/  MLX5E_FULLMATCH ; 
 int /*<<< orphan*/  mlx5_mpfs_del_mac (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mlx5e_add_eth_addr_rule (struct mlx5e_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_del_eth_addr_from_flow_table (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_del_eth_addr_from_hash (struct mlx5e_eth_addr_hash_node*) ; 

__attribute__((used)) static void
mlx5e_execute_action(struct mlx5e_priv *priv,
    struct mlx5e_eth_addr_hash_node *hn)
{
	switch (hn->action) {
	case MLX5E_ACTION_ADD:
		mlx5e_add_eth_addr_rule(priv, &hn->ai, MLX5E_FULLMATCH);
		hn->action = MLX5E_ACTION_NONE;
		break;

	case MLX5E_ACTION_DEL:
		mlx5e_del_eth_addr_from_flow_table(priv, &hn->ai);
		if (hn->mpfs_index != -1U)
			mlx5_mpfs_del_mac(priv->mdev, hn->mpfs_index);
		mlx5e_del_eth_addr_from_hash(hn);
		break;

	default:
		break;
	}
}