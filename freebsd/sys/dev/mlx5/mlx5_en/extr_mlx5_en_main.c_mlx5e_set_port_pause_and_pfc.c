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
struct TYPE_2__ {int /*<<< orphan*/  tx_priority_flow_control; int /*<<< orphan*/  rx_priority_flow_control; int /*<<< orphan*/  tx_pauseframe_control; int /*<<< orphan*/  rx_pauseframe_control; } ;
struct mlx5e_priv {TYPE_1__ params; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int mlx5_set_port_pause_and_pfc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx5e_set_port_pause_and_pfc(struct mlx5e_priv *priv)
{
	return (mlx5_set_port_pause_and_pfc(priv->mdev, 1,
	    priv->params.rx_pauseframe_control,
	    priv->params.tx_pauseframe_control,
	    priv->params.rx_priority_flow_control,
	    priv->params.tx_priority_flow_control));
}