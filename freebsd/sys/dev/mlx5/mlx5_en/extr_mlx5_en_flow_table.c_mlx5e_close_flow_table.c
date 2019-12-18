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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_destroy_inner_rss_flow_table (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_main_flow_table (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_vlan_flow_table (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_handle_ifp_addr (struct mlx5e_priv*) ; 

void
mlx5e_close_flow_table(struct mlx5e_priv *priv)
{

	mlx5e_handle_ifp_addr(priv);
	mlx5e_destroy_inner_rss_flow_table(priv);
	mlx5e_destroy_main_flow_table(priv);
	mlx5e_destroy_vlan_flow_table(priv);
}