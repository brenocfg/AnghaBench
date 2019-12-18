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
struct mlx5e_priv {int /*<<< orphan*/  counter_set_id; int /*<<< orphan*/  mdev; int /*<<< orphan*/  ifp; int /*<<< orphan*/  state; } ;
struct ifnet {struct mlx5e_priv* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_ETH ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_vport_dealloc_q_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_close_channels (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_close_flow_table (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_close_rqt (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_close_tirs (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_close_tises (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_del_all_vlan_rules (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_set_rx_mode_core (struct mlx5e_priv*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
mlx5e_close_locked(struct ifnet *ifp)
{
	struct mlx5e_priv *priv = ifp->if_softc;

	/* check if already closed */
	if (test_bit(MLX5E_STATE_OPENED, &priv->state) == 0)
		return (0);

	clear_bit(MLX5E_STATE_OPENED, &priv->state);

	mlx5e_set_rx_mode_core(priv);
	mlx5e_del_all_vlan_rules(priv);
	if_link_state_change(priv->ifp, LINK_STATE_DOWN);
	mlx5e_close_flow_table(priv);
	mlx5e_close_tirs(priv);
	mlx5e_close_rqt(priv);
	mlx5e_close_channels(priv);
	mlx5_vport_dealloc_q_counter(priv->mdev,
	    MLX5_INTERFACE_PROTOCOL_ETH, priv->counter_set_id);
	mlx5e_close_tises(priv);

	return (0);
}