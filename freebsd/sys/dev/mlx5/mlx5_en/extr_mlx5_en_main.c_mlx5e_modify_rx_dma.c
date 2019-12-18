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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int num_channels; } ;
struct mlx5e_priv {int /*<<< orphan*/ * channel; TYPE_1__ params; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  mlx5e_disable_rx_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_enable_rx_dma (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
mlx5e_modify_rx_dma(struct mlx5e_priv *priv, uint8_t value)
{
	int i;

	if (test_bit(MLX5E_STATE_OPENED, &priv->state) == 0)
		return;

	for (i = 0; i < priv->params.num_channels; i++) {
		if (value)
			mlx5e_disable_rx_dma(&priv->channel[i]);
		else
			mlx5e_enable_rx_dma(&priv->channel[i]);
	}
}