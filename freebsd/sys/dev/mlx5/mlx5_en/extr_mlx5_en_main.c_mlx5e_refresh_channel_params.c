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
struct TYPE_2__ {int num_channels; } ;
struct mlx5e_priv {int /*<<< orphan*/ * channel; TYPE_1__ params; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int mlx5e_refresh_channel_params_sub (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
mlx5e_refresh_channel_params(struct mlx5e_priv *priv)
{
	int i;

	/* check if channels are closed */
	if (test_bit(MLX5E_STATE_OPENED, &priv->state) == 0)
		return (EINVAL);

	for (i = 0; i < priv->params.num_channels; i++) {
		int err;

		err = mlx5e_refresh_channel_params_sub(priv, &priv->channel[i]);
		if (err)
			return (err);
	}
	return (0);
}