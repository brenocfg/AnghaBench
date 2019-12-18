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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  active_vlans; } ;
struct mlx5e_priv {int /*<<< orphan*/  state; TYPE_1__ vlan; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  MLX5E_VLAN_RULE_TYPE_MATCH_VID ; 
 int /*<<< orphan*/  PRIV_LOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  PRIV_UNLOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_del_vlan_rule (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
mlx5e_vlan_rx_kill_vid(void *arg, struct ifnet *ifp, u16 vid)
{
	struct mlx5e_priv *priv = arg;

	if (ifp != priv->ifp)
		return;

	PRIV_LOCK(priv);
	clear_bit(vid, priv->vlan.active_vlans);
	if (test_bit(MLX5E_STATE_OPENED, &priv->state))
		mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_VID, vid);
	PRIV_UNLOCK(priv);
}