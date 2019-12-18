#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int filter_disabled; } ;
struct mlx5e_priv {int /*<<< orphan*/  state; TYPE_2__* ifp; TYPE_1__ vlan; } ;
struct TYPE_4__ {int if_flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  mlx5e_del_any_vid_rules (struct mlx5e_priv*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
mlx5e_enable_vlan_filter(struct mlx5e_priv *priv)
{
	if (priv->vlan.filter_disabled) {
		priv->vlan.filter_disabled = false;
		if (priv->ifp->if_flags & IFF_PROMISC)
			return;
		if (test_bit(MLX5E_STATE_OPENED, &priv->state))
			mlx5e_del_any_vid_rules(priv);
	}
}