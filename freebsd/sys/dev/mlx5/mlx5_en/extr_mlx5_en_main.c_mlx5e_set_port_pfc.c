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
struct TYPE_2__ {scalar_t__ tx_pauseframe_control; scalar_t__ rx_pauseframe_control; } ;
struct mlx5e_priv {scalar_t__ gone; int /*<<< orphan*/  ifp; TYPE_1__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  mlx5_en_err (int /*<<< orphan*/ ,char*) ; 
 int mlx5e_set_port_pause_and_pfc (struct mlx5e_priv*) ; 

__attribute__((used)) static int
mlx5e_set_port_pfc(struct mlx5e_priv *priv)
{
	int error;

	if (priv->gone != 0) {
		error = -ENXIO;
	} else if (priv->params.rx_pauseframe_control ||
	    priv->params.tx_pauseframe_control) {
		mlx5_en_err(priv->ifp,
		    "Global pauseframes must be disabled before enabling PFC.\n");
		error = -EINVAL;
	} else {
		error = mlx5e_set_port_pause_and_pfc(priv);
	}
	return (error);
}