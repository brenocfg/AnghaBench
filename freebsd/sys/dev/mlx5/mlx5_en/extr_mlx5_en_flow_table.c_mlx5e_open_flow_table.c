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
struct TYPE_2__ {int /*<<< orphan*/  ns; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; TYPE_1__ fts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_KERNEL ; 
 int /*<<< orphan*/  mlx5_get_flow_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5e_create_inner_rss_flow_table (struct mlx5e_priv*) ; 
 int mlx5e_create_main_flow_table (struct mlx5e_priv*) ; 
 int mlx5e_create_vlan_flow_table (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_main_flow_table (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_vlan_flow_table (struct mlx5e_priv*) ; 

int
mlx5e_open_flow_table(struct mlx5e_priv *priv)
{
	int err;

	priv->fts.ns = mlx5_get_flow_namespace(priv->mdev,
					       MLX5_FLOW_NAMESPACE_KERNEL);

	err = mlx5e_create_vlan_flow_table(priv);
	if (err)
		return (err);

	err = mlx5e_create_main_flow_table(priv);
	if (err)
		goto err_destroy_vlan_flow_table;

	err = mlx5e_create_inner_rss_flow_table(priv);
	if (err)
		goto err_destroy_main_flow_table;

	return (0);

err_destroy_main_flow_table:
	mlx5e_destroy_main_flow_table(priv);
err_destroy_vlan_flow_table:
	mlx5e_destroy_vlan_flow_table(priv);

	return (err);
}